#include<SFML/Graphics.hpp>
#include<optional> 
#include<cmath> 
#include<iostream> 
#include<TGUI/TGUI.hpp> 
#include<TGUI/Backend/SFML-Graphics.hpp>
#include"ChatWindow.h"
#include"CircleManager.h"
#include"EdgeManager.h" 
#include"SimHUD.h" 

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
    sf::Clock simClock;                 // measures real time between frames 
    float simStepInterval = 0.1f;       // the limit for the accumulator (fills to this before one simulation step runs)
    float simAccumulaor = 0.0f;         // a bucket that fills with elapsed time 
    bool simRunning = false;            // for pause and play 
    int simStep = 0;                    // tracks number of simulation steps 

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
    button->setPosition({1920.0f - 100.0f, 0.0f});
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
    
    // MANAGERS 
    CircleManager manager;
    EdgeManager edgeManager(manager);  
    SimHUD hud; 

    // HUD 
    hud.loadFont("assets/arial/ARIAL.TTF"); 
    hud.setOffset({15.0f, 15.0f}); 

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

            // SET NODE TYPE & RUN SIMULATION (PRESS SPACE)
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
   
            // PLACE NODE(s) 
            if (const auto* key_event = ev->getIf<sf::Event::KeyPressed>()) {

                // E = place node 
                if (key_event->code == sf::Keyboard::Key::E) {
                    manager.placeCircle(window); 
                }

                // G = place grid 
                if (key_event->code == sf::Keyboard::Key::G) {
                    int start_index = manager.getNodes().size(); // get number before placing 100 nodes (so we know start and end nodes for this, all nodes between start and end are the grid)
                    manager.placeGrid(window); 
                    edgeManager.connectGridRange(start_index, 10, 10);
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
        if (simRunning) { // if space pressed 
            simAccumulaor += simClock.restart().asSeconds(); // adding elapsed time to the "bucket"
            if (simAccumulaor >= simStepInterval) { 
                // once time has accumulated to be greater than or equal to the "capacity of the bucket"
                // we run the moran process once          

                simAccumulaor -= simStepInterval;       // don't zero the buck but subtract the time we used to execute a step then start from the left over amount (this is more accurate than just 0-ing -> we are carrying that time over)
                manager.runMoranProcess();              // run a step 
                simStep++;                              // increment step counter

                // this is known as a fixed timestep accumulator pattern I've learned -> ensures stable behaviour and accurate long running sims 

            }               
        } else {
            // restarting the clock while paused so the time doesn't accumulate (basically keeps zeroing while paused), prevents jumps after resuming 
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

        // Count residents and mutants for HUD
        int residents = 0, mutants = 0;
        for (const auto& node : manager.getNodes()) {
            if (node->getType() == Node::Type::Resident) residents++;
            else mutants++;
        }
        hud.update(residents, mutants, simStep, simStepInterval, simRunning);
        hud.drawHUD(window); 


        window.display(); //draw new frame 

    }
}