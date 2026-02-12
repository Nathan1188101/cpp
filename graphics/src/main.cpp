#include<SFML/Graphics.hpp>
#include<optional> 
#include<cmath> 
#include<iostream> 
#include<TGUI/TGUI.hpp> 
#include<TGUI/Backend/SFML-Graphics.hpp>
#include"ChatWindow.h"
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

    // for sim tick rate 
    sf::Clock simClock; 
    float simStepInterval = 0.5f;
    float simAccumulaor = 0.0f; 
    bool simRunning = false; 

    // setting up window 
    unsigned int width = 1920; 
    unsigned int height = 1080; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "Main");
    window.setFramerateLimit(240); 
    window.setKeyRepeatEnabled(false); // disables key press events from being added to event queue while key held down. One adds event when key is first pressed, and not again until you lift and press again


    // create TGUI instance?  
    tgui::Gui gui{window};
    // TGUI button 
    auto button = tgui::Button::create("LLM"); // make a button 
    button->setPosition({0.0f, 0.0f});
    button->setSize(100, 50);
    gui.add(button); 


    // Create ChatWindow instance (now draggable)
    ChatWindow chat(gui, 400, 100, 300, 500);
    chat.addMessage("Welcome to the chat!", "System");

    // Toggle chat window when LLM button is clicked
    button->onPress([&chat]() {
        chat.toggle();
    });

    // camera 
    sf::View camera({width / 2.0f, height / 2.0f}, {1920.f, 1080.f}); // center at middle of window, and size of window  
     
    CircleManager manager;
    EdgeManager edgeManager(manager);  

    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {

            // Handle TGUI events (required for widget interaction like dragging)
            gui.handleEvent(*ev);

            if (ev->is<sf::Event::Closed>()) {
                window.close(); 
            }

            if (ev->is<sf::Event::Resized>()) {
                // need to figure out how to handle window resizing 
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

            // SET NODE TYPE 
            if (const auto* key_event = ev->getIf<sf::Event::KeyPressed>()) {
                // Skip game key bindings when typing in chat
                if (chat.isInputFocused()) {
                    continue;
                }

                if (key_event->code == sf::Keyboard::Key::C) {
                    std::cout << "C pressed" << std::endl; 
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
                    for (auto& node : manager.getNodes()) {
                        bool check = manager.isCircleClicked(window, mousePos, node->getPosition());
                        if (check) {
                            //node->setNodeStrategy(Node::Strategy::Cooperate);
                            node->setType(Node::Type::Resident); // fitness 1.0f 
                        }
                    } 
                }

                if (key_event->code == sf::Keyboard::Key::F) {
                    std::cout << "F pressed" << std::endl; 
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
                    for (auto& node : manager.getNodes()) {
                        bool check = manager.isCircleClicked(window, mousePos, node->getPosition());
                        if (check) {
                            //node->setNodeStrategy(Node::Strategy::Compete); 
                            node->setType(Node::Type::Mutant); 
                        }
                    } 
                }

                if (key_event->code == sf::Keyboard::Key::Space) {
                    simRunning = !simRunning;
                    std::cout << (simRunning ? "Simulation started" : "Simulation paused") << std::endl;
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

        
        // SIMULATION 
        if (simRunning) {
            simAccumulaor += simClock.restart().asSeconds();
            if (simAccumulaor >= simStepInterval) {

                simAccumulaor = 0.0f; 

                // set cooperate/compete for this round 
                // decide next action based on strat + last tick state 
                for (auto& node : manager.getNodes()) {
                    node->applyStrategy(); 
                }

                // commit all actions simultaneously 
                for (auto& node : manager.getNodes()) {
                    node->commitAction(); 
                }

                // score using commited actions
                for (auto& node : manager.getNodes()) {
                    node->computeScore(); 
                }

                // select strat for next round 
                for (auto& node : manager.getNodes()) {
                    node->selectStrategy(); 
                }

            } 
        } else {
            simClock.restart(); 
        }

       
        // MOVE CIRCLE WITH MOUSE 
        manager.moveSelectedCircle(window); 


        window.clear(); // clear last framed

        gui.draw(); // GUI elements 

        // ignore camera movement controls while focused on chat box 
        if (!chat.isInputFocused()) {
            movement(camera);
        } 
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