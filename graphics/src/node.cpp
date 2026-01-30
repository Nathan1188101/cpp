#include"Node.h" 
#include<SFML/Graphics.hpp> 
#include<cmath> 

// constructor definition 
Node::Node(sf::Vector2f position, float radius, sf::Color color)
    // initializer list 
    : radius(radius) // attach radius to Node (now every node will know its radius)
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

