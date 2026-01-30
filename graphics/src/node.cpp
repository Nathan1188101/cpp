#include"Node.h" 
#include<SFML/Graphics.hpp> 

// constructor definition 
Node::Node(sf::Vector2f position, float radius, sf::Color color = sf::Color::Green) {
    node.setRadius(radius); 
    node.setPosition(position); 
    node.setFillColor(color); 
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


