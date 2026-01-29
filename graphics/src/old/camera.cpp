#include<SFML/Graphics.hpp>
#include<optional> 
#include<cmath> 

int main(){     

    // setting up window 
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "camera");
    window.setFramerateLimit(60); 

    // camera 
    sf::View camera({width / 2.0f, height / 2.0f}, {800.f, 600.f}); // center at middle of window, and size of window 

    float radius = 50.0f;
    // circle 1
    sf::CircleShape c1(radius);
    c1.setOrigin(c1.getGeometricCenter()); // set center of circle
    c1.setFillColor(sf::Color::Blue); 
    c1.setPosition({(width / 2.0f) - 200.0f, height / 2.0f});

    // circle 2 
    sf::CircleShape c2(radius); 
    c2.setOrigin(c2.getGeometricCenter()); 
    c2.setFillColor(sf::Color::Red); 
    c2.setPosition({(width / 2.0f) + 200.0f, height / 2.0f}); 

    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) {
                window.close(); 
            }

            // capturing scroll wheel event (have to do it in the event loop because you can't continuosly hold the scroll wheel in a position like you can a keyboard press)
            // they are discrete, one-time 
            if (const auto* scroll = ev->getIf<sf::Event::MouseWheelScrolled>()) {
                if (scroll->delta > 0) {
                    camera.zoom(0.9f);  // scroll up = zoom in (smaller view)
                } else if (scroll->delta < 0) {
                    camera.zoom(1.1f);  // scroll down = zoom out (larger view)
                }
            }

        }

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

        // moving the circles 
        c1.move({1.0f, 0}); 
        c2.move({-1.0f, 0});

        // draw edge between circles
        // get positions of circles  
        sf::Vector2f p1 = c1.getPosition(); 
        sf::Vector2f p2 = c2.getPosition(); 

        // calculate the angle they form 
        float angle = atan2(p2.y - p1.y, p2.x - p1.x); 
        // now offset so edge goes to edge of circles 
        sf::Vector2f edge_start = p1 + sf::Vector2f(radius * cos(angle), radius * sin(angle)); 
        sf::Vector2f edge_end = p2 - sf::Vector2f(radius * cos(angle), radius * sin(angle)); 

        // set up the line 
        sf::Vertex line[] = {
            {edge_start}, {edge_end} 
        };

        window.clear(); // clear last frame

        window.setView(camera);

        // all drawing must be inbetween these 
        window.draw(c1);
        window.draw(c2); 
        window.draw(line, 2, sf::PrimitiveType::LineStrip); 

        window.display(); //draw new one

    }

}