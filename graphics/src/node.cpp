#include"node.h" 
#include<SFML/Graphics.hpp> 
#include<cmath> 
#include<iostream> 

// constructor definition 
Node::Node(sf::Vector2f position, float radius, int id,  sf::Color color)
    // initializer list 
    : radius(radius), // attach radius to Node (now every node will know its radius)
      id(id)
{
    node.setRadius(radius); 
    node.setPosition(position); 
    node.setFillColor(color); 
    node.setOrigin(node.getGeometricCenter()); 
}

/// @brief allows you to set position of node
/// @param pos pass in the position as a sf::Vector2f
void Node::setPosition(sf::Vector2f pos) {
    node.setPosition(pos); 
}

/// @brief returns position of node, uses sfml under the hood
/// @return position
sf::Vector2f Node::getPosition() const {
    return node.getPosition(); 
}

/// @brief sets selected state, also built in outline and thickness setting so don't worry about doing that yourself
/// @param sel selected = true, not selected = false 
void Node::setSelected(bool sel) {
    selected = sel; 
    node.setOutlineThickness(sel ? 3.0f : 0.0f); 
    node.setOutlineColor(sel ? sf::Color::Yellow : sf::Color::Transparent); 
}

/// @brief simply returns a bool "selected"
/// @return 
bool Node::isSelected() const {
    return selected; 
}

/// @brief function used to draw a node, just uses the sfml draw function
/// @param window need to pass in a ref to the window 
void Node::draw(sf::RenderWindow& window) const {
    window.draw(node); 
}

/// @brief set the outline color 
/// @param color is how to specify the color 
void Node::setOutlineColor(const sf::Color& color) {
    node.setOutlineColor(color); 
}

/// @brief allows you to set the outline thickness of a node
/// @param thickness is how you sepecifiy how thick (takes float)
void Node::setOutlineThickness(float thickness) {
    node.setOutlineThickness(thickness); 
}

bool Node::isClicked(const sf::RenderWindow& window, sf::Vector2i mousePos) const {

    // convert mouse pos to world pos 
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 

    // node pos 
    sf::Vector2f nodePos = node.getPosition(); 

    // euclidiean distance formula -> gets the straight line distance between two points (can do this more efficiently) -> the points being where your mouse is and the center of the circle
    float distance = std::sqrt(std::pow(worldPos.x - nodePos.x, 2) +
                                            std::pow(worldPos.y - nodePos.y, 2));

    return distance <= radius; 

}

/*
    add the neighbors a node has 
*/
void Node::addNeighbor(Node* node) {
    neighbors.push_back(node); 
}

// nothing changes here, we are just calculating how well each node did given the current round or "board"
void Node::computeScore() {

    // count total num of neighbors cooperating 
    int totalCooperators = 0; 
    for (Node* neighbor : neighbors) {
        if (neighbor->cooperate) {
            totalCooperators++;
        }
    }

    // so right now each neighboring cooperating node is contributing 0.8 points of benefit. 
    // right now there is more possible cooperation benefit on high-degree nodes
    // less on low degree nodes
    // apparently this is more realistic 
    // -> maybe I should make this value configureable by the user later

    if (cooperate) {
        score = (totalCooperators + 1) * 0.8f;
        
    } else {
        float bonus = neighbors.size() / 2.0f;
        score = (totalCooperators * 0.8f) + bonus; 
    }
    std::cout << id << "score: " << score << std::endl; 


}

// LOTS OF WORK TO BE DONE HERE, JUST TESTING FOR NOW 
/*
    this part uses the payoff to decide what to do next round
*/
void Node::selectStrategy() {

    if (score > 8) {
        strategy = Strategy::Compete; 
        node.setFillColor(sf::Color::Red); 
    } else if (score > 5) {
        strategy = Strategy::Cooperate;
        node.setFillColor(sf::Color::Blue);
    } else if (score < 3) {
        strategy = Strategy::Unforgiving;
        node.setOutlineThickness(3);
        node.setOutlineColor(sf::Color::Magenta); 
        // set color if you want
    } else { // score >= 3 && score <= 5
        strategy = Strategy::TitForTat;
        node.setOutlineThickness(3);
        node.setOutlineColor(sf::Color::Green); 
        // set color if you want
    }

}

// checks nodes strat and then sets the nod's action for the round 
void Node::applyStrategy() {
    switch(strategy) {
        case Strategy::Cooperate:
            nextCooperate = true;
            break; 
        case Strategy::Compete:
            nextCooperate = false; 
            break;
        case Strategy::TitForTat: { // (follow local majority) cooperate if more eighbors cooperated than defected, defect if more neighbors did that 
            int coopNeighbors = 0; 
            int compNeighbors = 0; 

            for (Node* neighbor : neighbors) {
                if (neighbor->cooperate) 
                    coopNeighbors++;
                else
                    compNeighbors++; 
                
            }

            // cooperate if majority is cooperating 
            nextCooperate = (coopNeighbors >= compNeighbors);
            break; 
        }

        case Strategy::Unforgiving: {
            int coopNeighbors = 0; 
            int compNeighbors = 0; 

            for (Node* n : neighbors) {
                if (n -> cooperate) 
                    coopNeighbors++; 
                else
                    compNeighbors++; 
            }

            // if  or more neighbors are defecting, join em
            if (compNeighbors >= neighbors.size() / 2) // need to tweak this threshold 
                nextCooperate = false;  
            else    
                nextCooperate = cooperate; // keep current action 

            break; 
        }
    }
}

// function for setting up initial state of nodes after placing them
void Node::setNodeStrategy(Strategy strat) {

    // set the strategy from what was passed in 
    strategy = strat; 
    score = 0; // clear score -> allows you to use already made graph and reset inital states 

    // set color based on strategy 
    if (strat == Strategy::Cooperate) {                                 // RESIDENT 
        cooperate = true; 
        node.setFillColor(sf::Color::Blue);  

        fitness = 1; 

        std::cout << id << " set to cooperate" << std::endl;
    } else if (strat == Strategy::Compete) {                            // DEFECTOR 
        node.setFillColor(sf::Color::Red);

        fitness = 1.05;   
      
        cooperate = false;
        std::cout << id << " set to compete" << std::endl; 
    }
   
}

/// @brief To change or set a node's type 
/// @param type can be Resident or Mutant 
void Node::setType(Type passed_type) {
    type = passed_type; 
    if (type == Type::Resident) {
        // resident 
        node.setFillColor(sf::Color::Blue); 
        fitness = 1.0f;                     // neutral fitness 
    } else if (type == Type::Mutant) {
        // a mutant
        node.setFillColor(sf::Color::Red);
        fitness = 2.0f; 
    }
}