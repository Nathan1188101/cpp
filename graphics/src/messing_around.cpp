#include<SFML/Graphics.hpp>
#include<iostream> 

int main() {

    sf::Clock clock; 

    // setting up window 
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "Main");
    window.setFramerateLimit(240);

    // create circle 
    sf::CircleShape circle; 
    circle.setRadius(30.0f); 
    circle.setOrigin(circle.getGeometricCenter()); 
    circle.setFillColor(sf::Color::White); 
    circle.setPosition({width / 2.0f, height / 2.0f});  

    sf::Vector2f velocity{0, 0}; 
    const float gravity = 500.0f; 

    while (window.isOpen()) {

        // measures frame times in seconds (resets clock every frame)
        // measures time since last frame 
        float dt = clock.restart().asSeconds();

        while (auto ev = window.pollEvent()) {

            // to close window 
            if (ev->is<sf::Event::Closed>()) {
                window.close(); 
            }

        }

        // apply gravity to velocity
        velocity.y += gravity * dt; // multiplying by the dt makes physics independent from frame rate (gravity is applied per second not per frame) since we can't rely on consistent frames (some quick, some slow) it would mess with the phyics 
        
        // velocity.x += gravity * dt; // horizontal force 

        // apply velocity to position
        circle.move(velocity * dt);

        // ground collision and bounce 
        float radius = circle.getRadius(); 
        sf::Vector2f pos = circle.getPosition(); 
        if (pos.y + radius > height) {
            pos.y = height - radius; 
            velocity.y *= -0.8f; 
            circle.setPosition(pos); 
        }

        if (pos.x + radius > width) {
            pos.x = width - radius; 
            velocity.x *= -0.8f; 
            circle.setPosition(pos); 
        }

        window.clear();
        window.draw(circle);
        window.display();

    }


}