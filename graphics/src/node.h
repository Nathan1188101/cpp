#pragma once 
#include<SFML/Graphics.hpp> 

/*
    lil' note for myself, seems like good advice. 

    when it comes to figuring out what to make public and private.

        -> just make everything private by default... 
        -> only make something public when other code really needs accses 
*/

class Node {
    public: 
        Node(sf::Vector2f position, float radius, int id, sf::Color color);                 // constructor

        enum class Strategy { Cooperate, Compete, Unforgiving, TitForTat };                 // possible strategies a node can employ, refer to as Node::Strategy

        void setPosition(sf::Vector2f pos);                                                 // sets position
        bool isClicked(const sf::RenderWindow& window, sf::Vector2i mousePos) const;        // will convert your Vector2i mousePos to world coordinates (DONT WORRY)
        sf::Vector2f getPosition() const;                                                   // returns position
        void setSelected(bool selected);                                                    // will set outline and outline thickness 
        bool isSelected() const;                                                            // returns if selected or not (T/F)
        void draw(sf::RenderWindow& window) const;                                          // draw circle
        void setOutlineColor(const sf::Color& color);                                       // set outline color 
        void setOutlineThickness(float thickness);                                          // set outline thickness 
        sf::CircleShape& getShape();                                                        // get ref to shape 
        const std::vector<Node*>& getNeighbors() const {return neighbors;}                  // (READ ONLY) get neighbors for node, with a promise to not modify the obj 
        void addNeighbor(Node* neighbor);                                                   // enables you to add a node as a neighbor to your current node
        int getId() const {return id;}                                                      // get node's Id 
        void computeScore();
        void selectStrategy();  
        void setNodeStrategy(Strategy strat);                                               // for setting initial state of a node after placing before running sim
        void applyStrategy(); 
        void commitAction() {cooperate = nextCooperate;} 
        void BirthDeath(); 
        int getTotalNodes() {return totalNodes;}
        float getFitness() {return fitness;}                                                // return a nodes fitness 

    private: 
        sf::CircleShape node;                   // node is a circle
        int id;                                 // Id
        float radius;                           // radius
        bool selected = false;                  // should mabye rename this since we also have a selected var in circleManager
        float score;                            // score
        Strategy strategy;                      // Strategy 
        std::vector<Node*> neighbors;           // (Linked list approach for tracing adjacent nodes) track a nodes neighbors (get a ref to them)
        bool cooperate = true;                  // represents nodes current action
        bool nextCooperate = true;              // staged action for next commit
        int totalNodes;                         // keep track of total number of nodes  
        float fitness = 1.0f;                            // for nodes fitness 
};
