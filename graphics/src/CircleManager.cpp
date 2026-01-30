#include"CircleManager.h"
#include<cmath> 

void CircleManager::placeCircle(const sf::RenderWindow& window) {
 
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 

        auto newNode = std::make_unique<Node>(worldPos, 50.0f, sf::Color::Green); 
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

    if (selected != nullptr) {
        selected->setOutlineThickness(0);
        selected = nullptr; 
    }
    for (auto& node : nodes) {
        node->setSelected(false); 
    }

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