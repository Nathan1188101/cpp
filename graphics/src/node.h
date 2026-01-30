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
        Node(sf::Vector2f position, float radius, sf::Color color); 

        void setPosition(sf::Vector2f pos); 
        bool isClicked(const sf::RenderWindow& window, sf::Vector2i mousePos) const; // will convert your Vector2i mousePos to world coordinates (DONT WORRY)
        sf::Vector2f getPosition() const; 
        void setSelected(bool selected); // not sure about this one 
        bool isSelected() const; 
        void draw(sf::RenderWindow& window) const; 
        void setOutlineColor(const sf::Color& color);
        void setOutlineThickness(float thickness);
        sf::CircleShape& getShape(); 
        


    private: 
        sf::CircleShape node; 
        int id; 
        float radius;
        bool selected = false; // should mabye rename this since we also have a selected var in circleManager

};
