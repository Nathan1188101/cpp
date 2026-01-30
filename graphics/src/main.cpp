#include<SFML/Graphics.hpp>
#include<optional> 
#include<cmath> 
#include<iostream> 
#include"CircleManager.h"
#include"EdgeManager.h" 

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
    sf::RenderWindow window(sf::VideoMode({width, height}), "Main");
    window.setFramerateLimit(240); 
    window.setKeyRepeatEnabled(false); // disables key press events from being added to event queue while key held down. One adds event when key is first pressed, and not again until you lift and press again

    // camera 
    sf::View camera({width / 2.0f, height / 2.0f}, {800.f, 600.f}); // center at middle of window, and size of window  
     
    CircleManager manager;
    EdgeManager edgeManager(manager);  

    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) {
                window.close(); 
            }
            // ZOOM CAMERA
            if (const auto* scroll = ev->getIf<sf::Event::MouseWheelScrolled>()) {
                if (scroll->delta > 0) {
                    camera.zoom(0.9f);  // scroll up = zoom in (smaller view)
                } else if (scroll->delta < 0) {
                    camera.zoom(1.1f);  // scroll down = zoom out (larger view)
                }
            }

            // SELECT NODE 
            if (const auto* click = ev->getIf<sf::Event::MouseButtonPressed>()) { 
                if (click->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = click->position;  // click position
                    manager.selectCircle(window, mousePos); 
                }
            }
   
            // PLACE NODE 
            if (const auto* key_event = ev->getIf<sf::Event::KeyPressed>()) {
                if (key_event->code == sf::Keyboard::Key::E) {
                    manager.placeCircle(window); 
                }
            }
        
            // detecting edge drag release 
            if (const auto* mouse_event = ev->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouse_event->button == sf::Mouse::Button::Right) {
                    std::cout << "Right mouse button released" << std::endl;  
                    edgeManager.EdgeDragRelease(window); 
                }
            }

            // START EDGE DRAG POSITION 
            if (const auto* mouse_event = ev->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse_event->button == sf::Mouse::Button::Right) {
                    edgeManager.getClickedCircleForEdgeToMouse(window); 
                }
            }
        }

        // MOVE CIRCLE 
        manager.moveSelectedCircle(window); 

        window.clear(); // clear last framed

        // camera movement 
        movement(camera); 
        window.setView(camera);

        // HANDLE DRAWING CIRCLES 
        manager.drawCircles(window); 

        // Current drag state (calculates edge for circle to mouse)
        edgeManager.EdgeStartToMouse(window); 
        // Draw edge to mosue
        edgeManager.DrawEdgeToMouse(window); 
        // Draw connected edges 
        edgeManager.DrawCompletedEdges(window); 


        window.display(); //draw new frame 

    }
}