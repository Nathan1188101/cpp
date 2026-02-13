#include<SFML/Graphics.hpp>
#include<iostream> 
#include<cmath> 

struct Ball {
    sf::CircleShape circle; 
    sf::Vector2f velocity; 

    Ball(sf::Vector2f position, float radius) {
        circle.setPosition(position);
        circle.setRadius(radius); 
        circle.setOrigin(circle.getGeometricCenter()); 
        circle.setFillColor(sf::Color::White); 
        velocity = {0, 0};  
    }

    sf::Vector2f getPosition() {return circle.getPosition();}
    float getRadius() {return circle.getRadius();} 
    void setPosition(sf::Vector2f position) {circle.setPosition(position);}
    void move(sf::Vector2f offset) {circle.move(offset);}
    void draw(sf::RenderWindow& window) {window.draw(circle);} 
};

std::vector<Ball> balls; 
float gravity_strength = 20.0f;

void placeBall(const sf::RenderWindow& window) {

    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 

    auto ball = Ball(worldPos, 20.0f);

    balls.push_back(ball);

}

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

    sf::Clock frame_clock; 
    sf::Clock GlobalClock; 

    // setting up window 
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "Main");
    window.setFramerateLimit(240);
    window.setKeyRepeatEnabled(false);  

    sf::View camera({width / 2.0f, height / 2.0f}, {800.0f, 600.0f});

    //sf::Vector2f velocity{0, 0}; 
    const float gravity = 500.0f; 

    while (window.isOpen()) {

        // measures frame times in seconds (resets clock every frame)
        // measures time since last frame 
        float dt = frame_clock.restart().asSeconds();

        // for global clock 
        float t = GlobalClock.getElapsedTime().asSeconds(); 

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

            if (const auto* key_pressed = ev->getIf<sf::Event::KeyPressed>()) {

                if (key_pressed->code == sf::Keyboard::Key::E) {
                    // place circle 
                    placeBall(window); 
                }

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

        for (auto& circle : balls) {
            
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            sf::Vector2f direction_vec = mousePos - circle.getPosition(); 
            float distance = std::sqrt(direction_vec.x * direction_vec.x + direction_vec.y * direction_vec.y); 
            sf::Vector2f push = {0, 0};
            if (distance > 0) {
                sf::Vector2f dir = direction_vec / distance; // normalize vector to extract distance 
                push = dir * gravity_strength; 
                circle.velocity.y += gravity * dt; // suppose this would be gravity (constant downward force of all circles)
                circle.move(circle.velocity * dt); 
            } 


        // ground collision and bounce 
        float radius = circle.getRadius(); 
        sf::Vector2f cirlce_pos = circle.getPosition(); // I KNOW IT'S SPELT WRONG 
        if (cirlce_pos.y + radius > height) {
            cirlce_pos.y = height - radius; 
            circle.velocity.y *= -0.8f; 
            circle.setPosition(cirlce_pos); 
        }
        if (cirlce_pos.y - radius < 0) {
            cirlce_pos.y = 0 + radius; 
            circle.velocity.y *= -0.8f; 
            circle.setPosition(cirlce_pos);
        }

        // horizontal force 
        if (cirlce_pos.x + radius > width) {
            cirlce_pos.x = width - radius; 
            circle.velocity.x *= -0.8f; 
            circle.setPosition(cirlce_pos); 
        } 
        if (cirlce_pos.x - radius < 0) {
            cirlce_pos.x = 0 + radius; 
            circle.velocity.x *= -0.8f; 
            circle.setPosition(cirlce_pos);  
        }

        if (distance <= radius * 2) { // random threshold to start

            circle.velocity -= push; 

        }


        }

        window.setView(camera); 

        
        sf::Color bg(
            50 + 50 * std::sin(t),
            20,
            100 + 50 * std::cos(t)
        );

        window.clear(bg);
        //window.clear();
        movement(camera); 
        //window.draw(circle);
        window.draw(line, 5, sf::PrimitiveType::LineStrip);
        for(auto& circle : balls) {
            circle.draw(window);  
        }
        window.display();

    }


}