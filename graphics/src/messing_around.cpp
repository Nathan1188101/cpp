#include<SFML/Graphics.hpp>
#include<iostream> 
#include<cmath> 

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

            // track mouse 
            if (const auto* mouseMoved = ev->getIf<sf::Event::MouseMoved>()) {
                std::cout << "new mouse x: " << mouseMoved->position.x << std::endl; 
                std::cout << "new mouse y: " << mouseMoved->position.y << std::endl; 
            }

        }

        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window)); 

        // to get our mouse to affect the movement of the cirlce 
        // we need to calculate the vector from the mouse to the ball 
        // normalize the vector (gives us direction) 
        // add a scaled version of that direction to the ball's velocity 
        
        // determine direction of velocity change 
        sf::Vector2f direction_vec = mousePos - circle.getPosition();
        // euclidean distance formula to get dstance from mouse to circle 
        float distance = std::sqrt(direction_vec.x * direction_vec.x + direction_vec.y * direction_vec.y);
        // normalize vector for direction 
        sf::Vector2f dir = direction_vec / distance; 
        float strength = 200.0f; 
        sf::Vector2f push = dir * strength;


        // apply gravity to velocity
        velocity.y += gravity * dt; // multiplying by the dt makes physics independent from frame rate (gravity is applied per second not per frame) since we can't rely on consistent frames (some quick, some slow) it would mess with the phyics 

        // apply velocity to position
        circle.move(velocity * dt);

        // ground collision and bounce 
        float radius = circle.getRadius(); 
        sf::Vector2f cirlce_pos = circle.getPosition(); // I KNOW IT'S SPELT WRONG 
        if (cirlce_pos.y + radius > height) {
            cirlce_pos.y = height - radius; 
            velocity.y *= -0.8f; 
            circle.setPosition(cirlce_pos); 
        }
        if (cirlce_pos.y + radius < 0) {
            cirlce_pos.y = 0 + radius; 
            velocity.y *= -0.8f; 
            circle.setPosition(cirlce_pos);
        }

        // horizontal force 
        if (cirlce_pos.x + radius > width) {
            cirlce_pos.x = width - radius; 
            velocity.x *= 0.8f; 
            circle.setPosition(cirlce_pos); 
        } 
        if (cirlce_pos.x + radius < 0) {
            cirlce_pos.x = 0 + radius; 
            velocity.x *= -0.8f; 
            circle.setPosition(cirlce_pos);  
        }

        if (distance <= radius) { // random threshold to start

            velocity += push; 

        }

        window.clear();
        window.draw(circle);
        window.display();

    }


}