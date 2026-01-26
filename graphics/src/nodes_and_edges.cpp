#include<SFML/Graphics.hpp>
#include<optional>
#include<cmath> 

int main(){
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "Nodes and Edges"); 
    window.setFramerateLimit(60); 

    // two cirlces 
    sf::CircleShape c1(50.0f);
    c1.setOrigin(c1.getGeometricCenter());
    c1.setPosition({(width / 2.0f) + 200.0f, height / 2.0f});
    c1.setFillColor(sf::Color::Blue); 
    
    sf::CircleShape c2(50.0f); 
    c2.setOrigin(c2.getGeometricCenter());
    c2.setPosition({(width / 2.0f) - 200.0f, height / 2.0f});
    c2.setFillColor(sf::Color::Red);

    sf::CircleShape c3(50.0f); 
    c3.setOrigin(c3.getGeometricCenter());
    c3.setPosition({width / 2.0f, (height / 2.0f) - 200.0f});
    c3.setFillColor(sf::Color::Yellow);

    // How to get edge between these two circles? 
    /*
        - use a vertex array for the line
        - use getPosition() to find the center of the circles 
        - calculate the angle for accurate line drawing between them 
        - calculate edge points 
    */
    
    while (window.isOpen()) {
        
        // checks every frame it checks the even queue 
        // pollEvent() retrieves events from OS like mouse clicks, key presses, etc. 
        // this inner while loop processes all queued events before continuing to the next frame 
        while (auto ev = window.pollEvent()) {
            // triggered when the x is pressed on the window 
            if (ev->is<sf::Event::Closed>()) {
                window.close(); 
            }
        }

        // calculate centers/connection points 
        sf::Vector2f p1 = c1.getPosition();
        sf::Vector2f p2 = c2.getPosition();  
        sf::Vector2f p3 = c3.getPosition(); 
        // use atan2 (from std c++ library) to calculate the angle between two points 
        float angle = std::atan2(p2.y - p1.y, p2.x - p1.x); // how far up/down, how far left/right (THIS GIVES US DISPLACEMENT) so it's like how far left/right do we go, and then how far up/down do we go to get to that point. 

        // create line 
        sf::Vertex line[] = {
            // these are done in pairs for the primitive type Lines 
            {p1}, {p2},
            {p2}, {p3},
            {p3}, {p1}
        };

        // creating line strip for more efficient path creation 
        sf::Vertex lineStrip[] = {
            {p1}, {p2}, {p3}, {p1}
        };


        window.clear(); // clears previous frame 

        // draw stuff here inbetween 
        window.draw(c1); 
        window.draw(c2); 
        window.draw(c3);  
        window.draw(lineStrip, 4, sf::PrimitiveType::LineStrip);

        window.display(); // displays new frame 

    }

}