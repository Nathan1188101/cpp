#include"EdgeManager.h" 
#include<cmath> 
#include<iostream> 
#include<algorithm> 

// (CONSTRUCTOR DEFINITION) This is the definition of the constructor declaration -> we define how we are handling it and what we do with it here
/*
    NOTES: 
    EdegeManager:: -> this means it is a method belonging to the EdgeManager class 
    EdgeManager(CircleManager& cm) -> means the constructor is taking a reference to a circle manager object named cm
    : circleManager(cm) -> the MEMBER INITIALIZER LIST, here we are storing cm (the circle manager ref) IN the private memeber variable circleManager 
*/
EdgeManager::EdgeManager(CircleManager& cm) : circleManager(cm) {}

void EdgeManager::getClickedCircleForEdgeToMouse(const sf::RenderWindow& window) {

    auto& circles_ref = circleManager.getCircles(); 

    // getting clicked circle for drag start pos 
    if (dragStartPos == nullptr) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
        for (int i = 0; i < circles_ref.size(); i++) {                
            if (circleManager.isCircleClicked(window, mousePos, circles_ref[i]->getPosition())) { 
                dragStartPos = circles_ref[i].get(); // store that circle 
                is_dragging_edge = true; 
                break; // stop searching 
            }
        }
    }

}

std::array<sf::Vertex, 2> EdgeManager::EdgeStartToMouse(const sf::RenderWindow& window) {

    float radius = circleManager.getRadius(); 

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
    sf::Vertex edge_to_mouse[] = { 
        {edge_start_drag}, {mousePos}
    };

    return {sf::Vertex{edge_start_drag}, sf::Vertex{mousePos}}; 
}

void EdgeManager::EdgeDragRelease(const sf::RenderWindow& window) {

    // DEBUGGING 
    std::cout << "EDGE DRAG RELEASE CALLED" << std::endl; 

    auto& circles = circleManager.getCircles(); 

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (int i = 0; i < circles.size(); i++) {
        sf::Vector2f circlePos = circles[i]->getPosition();  
        if (circleManager.isCircleClicked(window, mousePos, circlePos)) {
            // store this end circle 
            dragEndPos = circles[i].get(); 
            break; 
        }
    }
    
    // check to make sure edge doesn't already exist 
    auto& check_start = dragStartPos;
    auto& check_end = dragEndPos; 
    /*
        NOTES ABOUT THE LAMBDA FUNCTION:
        [&](const Edge& e) -> anonymous inline function to have each edge returned as a reference called e
                              this will return true if the edge already exists. 
    */
    auto it = std::find_if(edges.begin(), edges.end(), [&](const Edge& e){
        // checking edges in both directions
        return (e.start == check_start && e.end == check_end) ||
                (e.start == check_end && e.end == check_start);
    });
    if (it == edges.end()) {
        // edge doesn't exist, so we can add it (if the next validation passes)
        if (dragStartPos != nullptr && dragEndPos != nullptr && dragStartPos != dragEndPos) {
            edges.push_back({dragStartPos, dragEndPos});
        } 
    }

    // set back to null 
    dragStartPos = nullptr;
    dragEndPos = nullptr;

    // DEBUGGING  
    std::cout << "Edges Size = " << edges.size() << std::endl; 

    // SIGNAL to stop drawing edge (button has been released)
    is_dragging_edge = false;
}

void EdgeManager::DrawEdgeToMouse(sf::RenderWindow& window) {
    // HANDLE circle to mouse edge 
    auto edge_to_mouse = EdgeStartToMouse(window); 
    if (dragStartPos != nullptr) {
        window.draw(edge_to_mouse.data(), 2, sf::PrimitiveType::LineStrip);
    }
}

void EdgeManager::DrawCompletedEdges(sf::RenderWindow& window) {

    float radius = circleManager.getRadius(); 

    // draw finished connections 
    for (int i = 0; i < edges.size(); i++) {
        // for each edge get the start and end pos 
        sf::Vector2f start_pos = edges[i].start->getPosition();
        sf::Vector2f end_pos = edges[i].end->getPosition(); 
        // calculate angle
        float angle = atan2(start_pos.y - end_pos.y, start_pos.x - end_pos.x); 
        // calculate offset 
        sf::Vector2f edge_start = start_pos - sf::Vector2f(radius * cos(angle), radius * sin(angle));
        sf::Vector2f edge_end = end_pos + sf::Vector2f(radius * cos(angle), radius * sin(angle)); 
        sf::Vertex edge[] = {
            {edge_start} , {edge_end}
        };
        // draw 
        window.draw(edge, 2, sf::PrimitiveType::LineStrip); 
    }
}



