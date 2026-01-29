#include"CircleManager.h"
#include<cmath> 

void CircleManager::placeCircle(const sf::RenderWindow& window) {
 
        // get mouse pos 
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // pass in window to get postion relative to window (otherwise u get position on entire desktop)
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        auto newCircle = std::make_unique<sf::CircleShape>(radius); 
        circles.push_back(std::move(newCircle)); 
        circles.back()->setFillColor(sf::Color::Green); 
        circles.back()->setPosition({worldPos.x, worldPos.y});
        circles.back()->setOrigin(circles.back()->getGeometricCenter()); 

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

     // clear outline if there is one on a circle already
    if (selected != nullptr) {
        selected->setOutlineThickness(0.0f); 
        selected = nullptr;  
    }
    
    // convert to world coords (need this since we have camera)
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 
    // loop through all circles to see if any pressed 
    for (int i = 0; i < circles.size(); i++) {

        // get circle pos
        sf::Vector2f circlePos = circles[i]->getPosition();
        // call the function at each iteration
        bool check = isCircleClicked(window, mousePos, circlePos); 
        // if clicked, set selected and give outline
        if (isCircleClicked(window, mousePos, circlePos)) {  
            selected = circles[i].get();   
                circles[i]->setOutlineColor(sf::Color::Yellow);   
                circles[i]->setOutlineThickness(3.0f);    
                break; // only want one circle selected, so stop searching 
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
    for (int i = 0; i < circles.size(); i++) {
        window.draw(*circles[i]); 
    }
}