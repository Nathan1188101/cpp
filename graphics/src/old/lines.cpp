/*
    Trying to place nodes and draw edges between them 
*/

#include<SFML/Graphics.hpp>
#include<optional>
#include<cmath> 

int main(){
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "Nodes and Edges"); 
    window.setFramerateLimit(60); 

    int n = 24; 

    // vertex arrays 
    sf::VertexArray lines; 
    lines.setPrimitiveType(sf::PrimitiveType::Lines); 
    lines.resize(n);

    for (int i = 0; i < n; i++) {
        sf::Vector2f pos = {float(i * cos(i)), float(i * sin(i))};
        lines[i].color = sf::Color::Red; 

        lines[i].position = pos; 
        lines[i].position += {width / 4.0f, height / 4.0f}; 

    }

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


        window.clear(); // clears previous frame 

        // draw stuff here inbetween 
        window.draw(lines); 
        window.display(); // displays new frame 

    }

}