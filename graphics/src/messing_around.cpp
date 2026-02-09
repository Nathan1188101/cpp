#include<SFML/Graphics.hpp>
#include<iostream> 
#include<cmath> 

void movement(sf::View& camera) {

        // move camera based on key input  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            camera.move({-2.f, 0}); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            camera.move({2.f, 0}); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            camera.move({0, -2.f}); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            camera.move({0, 2.f}); 
        }

}

int main() {

    sf::Clock clock; 

    // setting up window 
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "Main");
    window.setFramerateLimit(240);

    // create circle 
    sf::CircleShape circle; 
    circle.setRadius(20.0f); 
    circle.setOrigin(circle.getGeometricCenter()); 
    circle.setFillColor(sf::Color::White); 
    circle.setPosition({width / 2.0f, height / 2.0f});  

    sf::View camera({width / 2.0f, height / 2.0f}, {800.0f, 600.0f});

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

            // ZOOM CAMERA
            if (const auto* scroll = ev->getIf<sf::Event::MouseWheelScrolled>()) {
                std::cout << "scrolling" << std::endl; 
                if (scroll->delta > 0) {
                    camera.zoom(0.9f);  // scroll up = zoom in (smaller view)
                } else if (scroll->delta < 0) {
                    camera.zoom(1.1f);  // scroll down = zoom out (larger view)
                }
            }


            // track mouse 
            if (const auto* mouseMoved = ev->getIf<sf::Event::MouseMoved>()) {
                std::cout << "new mouse x: " << mouseMoved->position.x << std::endl; 
                std::cout << "new mouse y: " << mouseMoved->position.y << std::endl; 
            }

        }

        // border around window 
        sf::Vector2f top_left = {0.0, 0.0};
        sf::Vector2f bottom_right = {800.0, 600.0};
        sf::Vector2f top_right = {800.0, 0}; 
        sf::Vector2f bottom_left = {0, 600.0};
        sf::Vertex line[] = {
            {top_left}, {top_right}, {bottom_right}, {bottom_left}, {top_left}
        };

        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Vector2f direction_vec = mousePos - circle.getPosition();
        // euclidean distance formula to get dstance from mouse to circle 
        float distance = std::sqrt(direction_vec.x * direction_vec.x + direction_vec.y * direction_vec.y);
        // normalize vector for direction 
        sf::Vector2f dir = direction_vec / distance; 
        float strength = 10.0f; 
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
        if (cirlce_pos.y - radius < 0) {
            cirlce_pos.y = 0 + radius; 
            velocity.y *= -0.8f; 
            circle.setPosition(cirlce_pos);
        }

        // horizontal force 
        if (cirlce_pos.x + radius > width) {
            cirlce_pos.x = width - radius; 
            velocity.x *= -0.8f; 
            circle.setPosition(cirlce_pos); 
        } 
        if (cirlce_pos.x - radius < 0) {
            cirlce_pos.x = 0 + radius; 
            velocity.x *= -0.8f; 
            circle.setPosition(cirlce_pos);  
        }

        if (distance <= cirlce_pos.x + radius || distance <= cirlce_pos.y + radius ) { // random threshold to start

            velocity += push; 

        }

        window.setView(camera); 
        window.clear();
        movement(camera); 
        window.draw(circle);
        window.draw(line, 5, sf::PrimitiveType::LineStrip);
        window.display();

    }


}