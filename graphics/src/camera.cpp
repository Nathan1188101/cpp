#include<SFML/Graphics.hpp>
#include<optional> 
#include<cmath> 

int main(){     
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "camera");
    window.setFramerateLimit(60); 

    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) {
                window.close(); 
            }
        }

        window.clear(); // clear last frame
        
        // all drawing must be inbetween these 

        window.display(); //draw new one

    }

}