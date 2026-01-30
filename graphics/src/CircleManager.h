#pragma once 
#include<SFML/Graphics.hpp>
#include "node.h"

class CircleManager {
    public: 
        void placeCircle(const sf::RenderWindow& window);
        void selectCircle(const sf::RenderWindow& window, sf::Vector2i mousePos);
        void moveSelectedCircle(const sf::RenderWindow& window); 
        void drawCircles(sf::RenderWindow& window);
        bool isCircleClicked(const sf::RenderWindow& windowRef, sf::Vector2i mousePos, const sf::Vector2f& circlePos); // (should potentially be a private memeber function because it's an internal selection check), but making it public for now

        // getters 
        float getRadius() const {return radius;} // so we can access the radius anywhere (by def a public getter, makes it read only)
        const std::vector<std::unique_ptr<Node>>& getNodes() const {return nodes;};

    private:
        // members 
        float radius = 50.0f; // this is stupid but I'm leaving it for now
        Node* selected = nullptr; // empty to start (nothing selected)
        std::vector<std::unique_ptr<Node>> nodes; 


            
};