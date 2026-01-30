#pragma once 
#include<SFML/Graphics.hpp>
#include"CircleManager.h" 

class EdgeManager {

    public: 
        // this tells me how to create the object of EdgeManager (needs ref to circle manager)
        EdgeManager(CircleManager& cm); // constructor declaration (Edge manager must take ref to circleManager when being created now)
        struct Edge {
            // I want to store the connection as a pair of pointers to the Nodes 
            // this will help us with moving circles, and keeping that edge connected as it moves since we have a ref to the Node itself. (not a copy) 
            // circles are using smart pointers so, this structure works out since that means a circles memory location won't chance ever. 
            Node* start; 
            Node* end; 
        };
        std::array<sf::Vertex, 2> EdgeStartToMouse(const sf::RenderWindow& window);
        void EdgeDragRelease(const sf::RenderWindow& window);
        void DrawEdgeToMouse(sf::RenderWindow& window); 
        void DrawCompletedEdges(sf::RenderWindow& window);
        void getClickedCircleForEdgeToMouse(const sf::RenderWindow& window); 

    private:
        CircleManager& circleManager; // make reference to a circle manager private (Don't tell user what we are doing with it)
        std::vector<Edge> edges;
        bool is_dragging_edge;
        //sf::CircleShape* dragStartPos = nullptr; 
        //sf::CircleShape* dragEndPos = nullptr;
        Node* dragStartPos = nullptr; 
        Node* dragEndPos = nullptr; 
}; 