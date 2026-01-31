#include"Node.h" 
#include<SFML/Graphics.hpp> 
#include<cmath> 
#include<iostream> 

// constructor definition 
Node::Node(sf::Vector2f position, float radius, int id,  sf::Color color)
    // initializer list 
    : radius(radius), // attach radius to Node (now every node will know its radius)
      id(id)
{
    node.setRadius(radius); 
    node.setPosition(position); 
    node.setFillColor(color); 
    node.setOrigin(node.getGeometricCenter()); 
}

void Node::setPosition(sf::Vector2f pos) {
    node.setPosition(pos); 
}

sf::Vector2f Node::getPosition() const {
    return node.getPosition(); 
}

void Node::setSelected(bool sel) {
    selected = sel; 
    node.setOutlineThickness(sel ? 3.0f : 0.0f); 
    node.setOutlineColor(sel ? sf::Color::Yellow : sf::Color::Transparent); 
}

bool Node::isSelected() const {
    return selected; 
}

void Node::draw(sf::RenderWindow& window) const {
    window.draw(node); 
}

void Node::setOutlineColor(const sf::Color& color) {
    node.setOutlineColor(color); 
}

void Node::setOutlineThickness(float thickness) {
    node.setOutlineThickness(thickness); 
}

bool Node::isClicked(const sf::RenderWindow& window, sf::Vector2i mousePos) const {

    // convert mouse pos to world pos 
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 

    // node pos 
    sf::Vector2f nodePos = node.getPosition(); 

    // euclidiean distance formula -> gets the straight line distance between two points (can do this more efficiently) -> the points being where your mouse is and the center of the circle
    float distance = std::sqrt(std::pow(worldPos.x - nodePos.x, 2) +
                                            std::pow(worldPos.y - nodePos.y, 2));

    return distance <= radius; 

}

/*
    add the neighbors a node has 
*/
void Node::addNeighbor(Node* node) {
    neighbors.push_back(node); 
}

// nothing changes here, we are just calculating how well each node did given the current "board"
void Node::computeScore() {

    // count total num of neighbors cooperating 
    int totalCooperators = 0; 
    for (Node* neighbor : neighbors) {
        if (neighbor->cooperate) {
            totalCooperators++;
        }
    }

    score = 0.0f; 
    if (strategy == Strategy::Cooperate) {
        score = (totalCooperators + 1) * 0.8; // WE WILL BE CHANGING THIS I THINK 
    } else if (strategy == Strategy::Compete) {
        score = (totalCooperators * 0.8f) + (neighbors.size() / 2.0f); 
    }
    std::cout << id << "score: " << score << std::endl; 


}

// LOTS OF WORK TO BE DONE HERE, JUST TESTING FOR NOW 
/*
    this part uses the payoff to decide what to do next round
*/
void Node::selectStrategy() {

    if (score > 8) {
        strategy = Strategy::Compete; 
        node.setFillColor(sf::Color::Red); 
    } else if (score > 5) {
        strategy = Strategy::Cooperate;
        node.setFillColor(sf::Color::Blue);
    } else if (score < 3) {
        strategy = Strategy::Unforgiving;
        node.setFillColor(sf::Color::Magenta); 
        // set color if you want
    } else { // score >= 3 && score <= 5
        strategy = Strategy::TitForTat;
        node.setFillColor(sf::Color::Green); 
        // set color if you want
    }

}

void Node::applyStrategy() {
    switch(strategy) {
        case Strategy::Cooperate:
            cooperate = true;
            break; 
        case Strategy::Compete:
            cooperate = false; 
            break;
        case Strategy::TitForTat: {
            int coopNeighbors = 0, compNeighbors = 0; 
            for(Node* neighbor : neighbors) {
                if (neighbor->cooperate) coopNeighbors++;
            }
            cooperate = (compNeighbors <= 2);
            break; 
        }
    }
}

// function for setting up initial state of nodes after placing them
void Node::setNodeStrategy(Strategy strat) {

    // set the strategy from what was passed in 
    strategy = strat; 

    // set color based on strategy 
    if (strat == Strategy::Cooperate) {
        node.setFillColor(sf::Color::Blue);  
        std::cout << id << " set to cooperate" << std::endl;
    } else if (strat == Strategy::Compete) {
        node.setFillColor(sf::Color::Red); 
        std::cout << id << " set to compete" << std::endl; 
    }
    
}





