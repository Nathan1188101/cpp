#include<SFML/Graphics.hpp>
#include<optional> 
#include<cmath> 
#include<iostream> 

float radius = 50.0f;
// vector of smart pointers 
std::vector<std::unique_ptr<sf::CircleShape>> circles;
std::vector<std::unique_ptr<sf::Vertex>> vertices;  


bool isCircleClicked(const sf::RenderWindow& windowRef, sf::Vector2i mousePos, const sf::Vector2f& circlePos) {

    // convert to world coords (need this since we have camera)
    sf::Vector2f worldPos = windowRef.mapPixelToCoords(mousePos); 

    // euclidiean distance formula -> gets the straight line distance between two points (can do this more efficiently) -> the points being where your mouse is and the center of the circle
    float distance = std::sqrt(std::pow(worldPos.x - circlePos.x, 2) +
                                            std::pow(worldPos.y - circlePos.y, 2));

    return distance <= radius; 
}

void placeCircle(const sf::RenderWindow& window) {

        // handling new circle placement 
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            // get mouse pos 
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); // pass in window to get postion relative to window (otherwise u get position on entire desktop)
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            
            auto newCircle = std::make_unique<sf::CircleShape>(radius); 
            circles.push_back(std::move(newCircle)); 
            circles.back()->setFillColor(sf::Color::Green); 
            circles.back()->setPosition({worldPos.x, worldPos.y});
            circles.back()->setOrigin(circles.back()->getGeometricCenter()); 

        //}

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

    // setting up window 
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "Place Nodes");
    window.setFramerateLimit(240); 
    window.setKeyRepeatEnabled(false); // disables key press events from being added to event queue while key held down. One adds event when key is first pressed, and not again until you lift and press again

    // camera 
    sf::View camera({width / 2.0f, height / 2.0f}, {800.f, 600.f}); // center at middle of window, and size of window 

    // ref to selected circle 
    sf::CircleShape* selected = nullptr; // empty to start (nothing selected)
    sf::CircleShape* dragStartPos = nullptr;  

    float radius = 50.0f;
    
    // circle 1
    //sf::CircleShape c1(radius);
    auto c1 = std::make_unique<sf::CircleShape>(radius);
    (*c1).setOrigin((*c1).getGeometricCenter()); // set center of circle
    (*c1).setFillColor(sf::Color::Blue); 
    (*c1).setPosition({(width / 2.0f) - 200.0f, height / 2.0f});
    circles.push_back(std::move(c1));

    // circle 2 
    //sf::CircleShape c2(radius); 
    auto c2 = std::make_unique<sf::CircleShape>(radius);
    (*c2).setOrigin((*c2).getGeometricCenter()); 
    (*c2).setFillColor(sf::Color::Red); 
    (*c2).setPosition({(width / 2.0f) + 200.0f, height / 2.0f});
    circles.push_back(std::move(c2));

    // to detect dragging edge 
    bool is_dragging_edge; 

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

            /*
            NOTES: 
                 const because read only, it's an event (don't mutate it)
                 auto because we let the compiler figure out the type, otherwise I'd have to type that whole sf::Event::blahblah...
                 pointer (*) because it's simpler and faster. we just want to know if an event is there or not. either "something" or nullptr
            */
            // handle selection outline (triggers once per press, good for "just pressed"/selection logic)
            if (const auto* click = ev->getIf<sf::Event::MouseButtonPressed>()) { // getIf<>() -> means get if <it's this event>() 

                // handling selection of node in here (just does outline atm)
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
                    for (int i = 0; i < circles.size(); i++) {

                        // get circle pos
                        sf::Vector2f circlePos = circles[i]->getPosition();

                        // call the function at each iteration
                        bool check = isCircleClicked(window, mousePos, circlePos);

                        // if clicked, set selected and give outline
                        if (check) {  
                            selected = circles[i].get(); // was passing in ref but cirlce_array[i] will now return a ref itself, so we can just do this    
                            circles[i]->setOutlineColor(sf::Color::Yellow);   
                            circles[i]->setOutlineThickness(3.0f);    
                            break; // only want one circle selected, so stop searching 
                        } 
                    }
                
                }
            
            }

            // track mouse movement (DEBUG) 
            if (const auto* mouseMoved = ev->getIf<sf::Event::MouseMoved>()) {
                std::cout << "new mouse x: " << mouseMoved->position.x << std::endl; 
                std::cout << "new mouse y: " << mouseMoved->position.y << std::endl; 
            }
        
            // place new cicle.                     use event poll loop to detect key press, won't continuously update event queue now with having that disabled near the top of code
            if (const auto* key_event = ev->getIf<sf::Event::KeyPressed>()) {
                if (key_event->code == sf::Keyboard::Key::E) {
                    placeCircle(window); 
                }
            }
        
            if (const auto* mouse_event = ev->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouse_event->button == sf::Mouse::Button::Right) {
                    std::cout << "Right mouse button released" << std::endl;  
                    is_dragging_edge = false;
                }
            }
        }

        // (click and drag) handling node movement <- used to be in event poll loop which was wrong, and why we were getting weird node movement bugs
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selected != nullptr) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 
            selected->setPosition({worldPos.x, worldPos.y}); 
        }

        // handling edge function
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
             is_dragging_edge = true; 
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); 

            for (int i = 0; i < circles.size(); i++) {                
                if (isCircleClicked(window, mousePos, circles[i]->getPosition())) { 
                    dragStartPos = circles[i].get(); // store that circle 
                    break; // stop searching 
                }
            }
        }

        if (!is_dragging_edge) {
            dragStartPos = nullptr; 
        }

        sf::Vector2f circlePos;
        if (dragStartPos != nullptr){
            circlePos = dragStartPos->getPosition();  
        }
        sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))); 
        float mouse_angle = atan2(mousePos.y - circlePos.y, mousePos.x - circlePos.x); 
        sf::Vector2f edge_start_drag = circlePos + sf::Vector2f(radius * cos(mouse_angle), radius * sin(mouse_angle));
        sf::Vertex edge[] = { 
            {edge_start_drag}, {mousePos}
        };

        // camera movement 
        movement(camera); 

        // draw edge between circles
        // get positions of circles  
        sf::Vector2f p1 = circles[0]->getPosition(); // after moving c1 and c2 into the smart pointer vector, that's where they are. So you have to access them through their "new owner" by going through circles. 
        sf::Vector2f p2 = circles[1]->getPosition(); 
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

        // all drawing must be inbetween clear and display  
        for (int i = 0; i < circles.size(); i++) {
            window.draw(*circles[i]); 
        }

        window.draw(line, 2, sf::PrimitiveType::LineStrip); 

        if (dragStartPos != nullptr) {
            window.draw(edge, 2, sf::PrimitiveType::LineStrip);
        }

 


        window.display(); //draw new one

    }
}