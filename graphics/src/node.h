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
        Node(sf::Vector2f position, float radius, sf::Color color = sf::Color::Green); 

        void setPosition(sf::Vector2f pos); 
        sf::Vector2f getPosition() const; 
        void setSelected(bool selected); // not sure about this one 
        bool isSelected() const; 
        void draw(sf::RenderWindow& window) const; 
        sf::CircleShape& getShape(); 
        


    private: 
        sf::CircleShape node; 
        sf::CircleShape* selected = nullptr; // empty to start (nothing selected)
        int id; 
        float radius; 


};
