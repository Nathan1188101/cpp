#include<SFML/Graphics.hpp>
#include<optional> 
#include<cmath> 

bool isCirclClicked(const sf::RenderWindow& windowRef, sf::Vector2i mousePos, const sf::Vector2f& circlePos, float radius) {

    // convert to world coords (need this since we have camera)
    sf::Vector2f worldPos = windowRef.mapPixelToCoords(mousePos); 

    // euclidiean distance formula -> gets the straight line distance between two points (can do this more efficiently) 
    float distance = std::sqrt(std::pow(worldPos.x - circlePos.x, 2) +
                                            std::pow(worldPos.y - circlePos.y, 2));

    return distance <= radius; 
}

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

    // ref to selected circle 
    sf::CircleShape* selected = nullptr; // empty to start (nothing selected) 
    std::vector<sf::CircleShape*> circle_array = {&c1, &c2};

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

            // const because read only, it's an event (don't mutate it)
            // auto because we let the compiler to figure out the type, otherwise I'd have to type that whole sf::Event::blahblah...
            // pointer (*) because it's simpler and faster. we just want to know if an event is there or not. either "something" or nullptr
            if (const auto* click = ev->getIf<sf::Event::MouseButtonPressed>()) { // getIf<>() -> means get if <it's this event>() 
                if (click->button == sf::Mouse::Button::Left) {

                    // clear outline if there is one on a circle already
                    if (selected != nullptr) {
                        selected->setOutlineThickness(0.0f); 
                        selected = nullptr;  
                    }
                    
                    // get mouse position in window coords (relative to top left of window type of thing)
                    sf::Vector2i mousePos = click->position;

                    // convert to world coords (need this since we have camera)
                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 

                    // loop through all circles to see if any pressed 
                    for (int i = 0; i < circle_array.size(); i++) {

                        // get circle pos
                        sf::Vector2f circlePos = circle_array[i]->getPosition();

                        // call the function at each iteration
                        bool check = isCirclClicked(window, mousePos, circlePos, radius);

                        // we are checking how far the click is from the circle center 
                        if (check) {  
                            selected = circle_array[i]; // was passing in ref but cirlce_array[i] will now return a ref itself, so we can just do this    
                            circle_array[i]->setOutlineColor(sf::Color::Yellow);   
                            circle_array[i]->setOutlineThickness(5.0f);    
                        } 
                    }
                
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