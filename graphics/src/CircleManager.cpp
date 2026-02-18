#include"CircleManager.h"
#include<cmath> 
#include<random> 
#include<iostream>

void CircleManager::placeCircle(const sf::RenderWindow& window) {
 
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 

        auto newNode = std::make_unique<Node>(worldPos, 50.0f, nextNodeId++, sf::Color::White); 
        nodes.push_back(std::move(newNode)); 

}

// PRIVATE (INTERNAL) FUNCTION 
bool CircleManager::isCircleClicked(const sf::RenderWindow& windowRef, sf::Vector2i mousePos, const sf::Vector2f& circlePos) {

    // convert to world coords (need this since we have camera)
    sf::Vector2f worldPos = windowRef.mapPixelToCoords(mousePos); 

    // euclidiean distance formula -> gets the straight line distance between two points (can do this more efficiently) -> the points being where your mouse is and the center of the circle
    float distance = std::sqrt(std::pow(worldPos.x - circlePos.x, 2) +
                                            std::pow(worldPos.y - circlePos.y, 2));

    return distance <= radius; 
}

void CircleManager::selectCircle(const sf::RenderWindow& window, sf::Vector2i mousePos) {

    // if something is selected, set it to not be for selected pointer from CircleManager
    if (selected != nullptr) {
        selected->setOutlineThickness(0);
        selected = nullptr; 
    }
    
    // loop through all nodes and also set them to not selected
    for (auto& node : nodes) {
        node->setSelected(false); 
    }

    // loop through to see if any node was clicked, and select if so. 
    for (auto& node : nodes) {
        if (node->isClicked(window, mousePos)) {
            node->setSelected(true); 
            selected = node.get(); 
            break; 
        }
    }
}

void CircleManager::moveSelectedCircle(const sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selected != nullptr) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 
        selected->setPosition({worldPos.x, worldPos.y}); 
    }
}                

void CircleManager::drawCircles(sf::RenderWindow& window) {
    // HANDLE DRAWING CIRCLES 
    for (auto& node : nodes) {
        node->draw(window); 
    }
}

void CircleManager::runMoranProcess() {
    if (nodes.empty()) return; // don't run 

    // Sum all fitness values so we can select a node for reproduction 
    // individuals with higher fitness (r > 1) increase their share of the total "fitness pool"
    // this increases their prob of being picked (not guarenteed, just slightly biased)
    // (refer to pg. 100 in Evolutionary Dynamics)

    // so selection for reproduction should be weighted by fitness, and selection for death is uniform random 

    // get total fitness 
    float total_fitness = 0.0f;
    for (auto& node : nodes) {
        total_fitness += node->getFitness(); 
    }
    // quick check to see if there was an error computing total fitness 
    if (total_fitness <= 0) {
        std::cout << "DEBUG: total fitness = " << total_fitness << std::endl; 
    }

    // now we that we have total fitness we need to generate a random number between 0 and total fitness F, or formally -> r e (0, F)
    // then walk through nodes accumulating fitness
    // the first node we get two where accumulated fitness is => the random value, is the node selected for reproduction 
    
    // random number 
    static std::mt19937 rng(std::random_device{}()); // generate random seed value, which ensures random numbers everytime it's run
    std::uniform_real_distribution<float> dist(0.0f, total_fitness); // random number within bounds 0 to total fitness 
    float random_threshold = dist(rng); 

    Node* parent = nullptr; // remember to initialize to nullptr so we don't get it filled with garbage values 
    float sum = 0.0f; 
    for (auto& node : nodes) {
        sum += node->getFitness(); 
        if (sum >= random_threshold) {
            // this is the node selected for reproduction 
            parent = node.get(); 
            break; 
        }
    }
    if (!parent) {
        std::cout << "DEBUG: no parent selected" << std::endl; 
        return; // get out and don't do the rest 
    }

    // now we have selected a node for reproduction 
    // we need to choose one of it's neighbors uniform randomly (1/def(parent)) for death 
    
    // generate random number between the lower and upper bound of neighbors 
    // then select that neighbor for death 
    auto& neighbors = parent->getNeighbors();
    if (neighbors.empty()) {
        std::cout << "DEBUG: selected parents has no neighbors!" << std::endl;
        return; 
    }
    std::uniform_int_distribution<size_t> dist_neighbor(0, neighbors.size() - 1); 
    size_t random_neighbor = dist_neighbor(rng); 
    Node* for_death = neighbors[random_neighbor]; // NEED TO REPLACE THIS ONE -> with offspring of parent node 

    // replacement 
    for_death->setType(parent->getType()); 
    std::cout << "Node " << parent->getId() << " reproduced -> Node " << for_death->getId() << " was replaced" << std::endl; 

}

void CircleManager::placeGrid(const sf::RenderWindow& window) {
   
    // get mouse position and map it to the coordinates of the world (accounts for zooming and camera movement)
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
    sf::Vector2f start = window.mapPixelToCoords(mousePos); 

    // position is where the mouse is 
    sf::Vector2f position = start;
    int count = 0; 

    // can chance count to increase or decrease size of grid (need to also chance for loop inside)
    while (count < 10) {

        // reset x position back to mouse x position 
        position.x = start.x; 

        // horizontal part of the grid (chance the bound for i (10 right now) to increase or decrease the dimensions of the grid)
        for (int i = 0; i < 10; i++) {

            auto newNode = std::make_unique<Node>(position, 50.0f, nextNodeId++, sf::Color::White); 
            nodes.push_back(std::move(newNode));
            nodes.back()->setType(Node::Type::Resident); // all nodes in grid will be resident for now 
            position.x += 200.0f; 

        }

        position.y += 200.0f; 
        count++; 

    }

}

/// @brief function to place a pre-made star graph (hub and spoke)
/// @param window 
void CircleManager::placeStar(const sf::RenderWindow& window) {

}

/// @brief to delete all circles present in the sim so you can start over 
void CircleManager::deleteAllNodes() {
    nodes.clear(); // deletes all Node objects and removes null spaces from the vector 
    nextNodeId = 0; 
}

void CircleManager::setAllMutantFitness(float mutant_fitness) {
    // loop through all nodes and set mutant fitness to whatever fitness value passed in
    for (auto& node : nodes) { 
        // update the mutant fitness default value 
        node->setMutantFitness(mutant_fitness);
        if (node->getType() == Node::Type::Mutant){
           node->setType(Node::Type::Mutant); 
           // may not look obviosuy from this, however, this will re-apply the mutant fitness for already placed nodes
           // before this the default value was getting updated, but not apply to already existing mutants
           // this changes the mutant fitness for already placed nodes as well now by calling the setType() function
           // on said node again (which inside sets their fitness)
        }
        
    }
}

