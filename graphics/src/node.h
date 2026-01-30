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
        // if u need something, just make a getter 
        float getRadius(){return radius;}
        int getID(){return id;}
        


    private: 
        sf::CircleShape node; 
        sf::CircleShape* selected = nullptr; // empty to start (nothing selected)
        int id; 
        float radius; 


};
