#include"EdgeManager.h" 
#include<cmath> 
#include<iostream> 
#include<algorithm> 

// (CONSTRUCTOR DEFINITION) This is the definition of the constructor declaration -> specifying what it needs when creating one kind of thing
/*
    NOTES: 
    EdegeManager:: -> this means it is a method belonging to the EdgeManager class 
    EdgeManager(CircleManager& cm) -> means the constructor is taking a reference to a circle manager object named cm
    : circleManager(cm) -> the MEMBER INITIALIZER LIST, here we are storing cm (the circle manager ref) IN the private memeber variable circleManager 
*/
EdgeManager::EdgeManager(CircleManager& cm) : circleManager(cm) {}

/*
    this is for getting the start node for drawing edge from node to mouse 

    we make sure dragStartPos is null before proceeding 
    loop through all nodes -> check which one was clicked 
    once we find target set it as the dragStartPos, and set is_dragging_edge to true. 
    break to stop searching for more. 
*/
void EdgeManager::getClickedCircleForEdgeToMouse(const sf::RenderWindow& window) {

    // getting all nodes 
    auto& nodes = circleManager.getNodes(); 

    // make sure we aren't already dragging from somewhere 
    if (dragStartPos == nullptr) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // getting mouse pos 
        for (auto& node : circleManager.getNodes()) {           // looping through all nodes 
            if (node->isClicked(window, mousePos)) {            // checking each of these nodes to see if they've been clicked 
                dragStartPos = node.get();                      // 
                is_dragging_edge = true;                        
                break; 
            }
        }
    }

}

/// @brief This basically tracks from the start node (where you clicked to begin the edge drag) to your mouse
/// @param window is a ref to the window
/// @return returns an array that holds two vectors (start node and your mouse)
std::array<sf::Vertex, 2> EdgeManager::EdgeStartToMouse(const sf::RenderWindow& window) {

    // get the radius of a circle 
    float radius = circleManager.getRadius(); 

    // if we aren't dragging and edge make sure start pos is null 
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

/*
    HOW IT WORKS: 
    When we let go of right mouse button
    we want to see if that happened in a node (like within the radius/diameter of a node)
    if so, we grab that as the end pos, grab start pos we already have, and create this pair 
    then when done, we clear start and end because we've let go and are no longer dragging 
    also set is_dragging_edge to false, as we are not dragging.
*/
void EdgeManager::EdgeDragRelease(const sf::RenderWindow& window) {

    // DEBUGGING 
    std::cout << "EDGE DRAG RELEASE CALLED" << std::endl; 

    sf::Vector2i mousePos = sf::Mouse::getPosition(window); 

    // check if node was released on 
    for (auto& node : circleManager.getNodes()) {
        if (node->isClicked(window, mousePos)) {
            // store end circle pos 
            dragEndPos = node.get(); 
            break; // stop searching 
        }
    }

    // ref for checking 
    auto& check_start = dragStartPos; 
    auto& check_end = dragEndPos; 

    // check to make sure this edge doesn't already exist 
    auto it = std::find_if(edges.begin(), edges.end(), [&](const Edge& e){ // I need to go over again what this form means (some kind of anonomous function I remeber that returns )
        // check edges, both directions 
        // returns "if this or this"  
        return (e.start == check_start && e.end == check_end) ||
                (e.start == check_end && e.end == check_start);
    });
    if (it == edges.end()) {
        // if return nothing -> edge doesn't exist 
        if (dragStartPos != dragEndPos && dragStartPos != nullptr && dragEndPos != nullptr) {
            // create the pair (then we can draw the edge in DrawCompletedEdges())
            edges.push_back({dragStartPos, dragEndPos}); 

            // need to update these nodes neighbors 
            dragStartPos->addNeighbor(dragEndPos);
            dragEndPos->addNeighbor(dragStartPos); 

            // DEBUGGING
            std::cout << dragStartPos->getId() << "'s total neighbors: " << dragStartPos->getNeighbors().size() << std::endl; 
            std::cout << dragEndPos->getId() << "'s total neighbors: " << dragEndPos->getNeighbors().size() << std::endl; 

        }
    }

    // set both to null when done 
    dragStartPos = nullptr; 
    dragEndPos = nullptr;

    // DEBUGGING 
    std::cout << "Edges: " << edges.size() << std::endl; 
    
    is_dragging_edge = false; // done dragging 
}

/// @brief draws the edge from a selected start node to your mouse 
/// @param window 
void EdgeManager::DrawEdgeToMouse(sf::RenderWindow& window) {
    // HANDLE circle to mouse edge 
    auto edge_to_mouse = EdgeStartToMouse(window); 
    if (dragStartPos != nullptr) {
        window.draw(edge_to_mouse.data(), 2, sf::PrimitiveType::LineStrip);
    }
}

/// @brief draws all completed connections 
/// @param window 
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

/// @brief for making edges, it will do all necessary checks to ensure no duplicate or null node edges are made
/// @param a node a
/// @param b node b
void EdgeManager::makeEdge(Node* a, Node* b) {

    if (a == nullptr || b == nullptr) return; // exit early if one is null 

    // check to make sure this edge doesn't already exist 
    auto it = std::find_if(edges.begin(), edges.end(), [&](const Edge& e){ 
        // check edges, both directions 
        // returns "if this or this"  
        return (e.start == a && e.end == b) ||
                (e.start == b && e.end == a);
    });

    // .end() means not found, therefore edge doesn't exist AND WE CAN CREATE IT
    if (it == edges.end()) {
        
        if (a != b && a != nullptr && b != nullptr) {
            // create the pair (then we can draw the edge in DrawCompletedEdges())
            edges.push_back({a, b}); 

            // make each a neighbor of eachother 
            a->addNeighbor(b);
            b->addNeighbor(a); 

            // DEBUGGING
            std::cout << a->getId() << "'s total neighbors: " << a->getNeighbors().size() << std::endl; 
            std::cout << b->getId() << "'s total neighbors: " << b->getNeighbors().size() << std::endl; 

        }
    }

}

/// @brief Used for the grid craetion function to connect all the nodes together accordingly
/// @param startIndex is so we now which node to start at and then we can go + 100 from that for the target nodes
/// @param rows number of rows
/// @param cols number of columns 
void EdgeManager::connectGridRange(size_t startIndex, int rows, int cols) {

    // GOT AI TO MAKE THIS EDGE CONNECTOR FOR THE GRID FOR ME USING MY makeEdge FUNCTION AND WHAT NOT
    // I WILL COME BACK LATER TO STUDY THIS BUT I NEE TO PICK UP THE PACE AND WORK ON OTHER
    // PARTS OF THIS FOR NOW!! 

    auto& nodes = circleManager.getNodes();

    // safety: ensure we have enough nodes
    size_t needed = startIndex + static_cast<size_t>(rows * cols);
    if (nodes.size() < needed) return;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            size_t idx = startIndex + static_cast<size_t>(r * cols + c);
            Node* a = nodes[idx].get();

            // right neighbor
            if (c + 1 < cols)
            {
                Node* right = nodes[idx + 1].get();
                makeEdge(a, right);
            }

            // down neighbor
            if (r + 1 < rows)
            {
                Node* down = nodes[idx + static_cast<size_t>(cols)].get();
                makeEdge(a, down);
            }
        }
    }
}
