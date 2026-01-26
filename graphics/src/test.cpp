#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "SFML 3 Test");
    window.setFramerateLimit(60); 
    
    // circle stuff 
    sf::CircleShape circle(80.0f); // sets radius (size) of circle 
    circle.setOrigin(circle.getGeometricCenter()); // makes it so when we set the pos, or rotate the circle, it will all be done based on it's center (rather than a point at it's "top left").
    float x = 0.0; 
    float y = 0.0; 
    circle.setPosition({width / 2.0f, height / 2.0f});
    circle.setFillColor(sf::Color::Green); // set color (inner)
    circle.setOutlineThickness(3.0f);
    circle.setOutlineColor(sf::Color::Magenta); 
    circle.setPointCount(3); 


    // rectangle stuff 
    sf::RectangleShape rectangle({50.0f, 80.0f}); 
    rectangle.setOrigin(rectangle.getSize() / 2.0f); 
    rectangle.setPosition({width / 2.0f, height / 2.0f});
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setOutlineThickness(5.0f); 
    rectangle.setOutlineColor(sf::Color::Blue);
    
    // convex shape 
    sf::ConvexShape convex; 
    convex.setPointCount(3); 
    convex.setPoint(0, {}); 



    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // rotate shape 
        circle.rotate(sf::degrees(1.0f)); 
        // move (translate)
        circle.move({1.0f, -1.0f}); // y axis inverted in sfml (negaitve is up, positive is down)

        rectangle.rotate(sf::degrees(1)); 

        // collisions 
        circle.setFillColor(sf::Color::Magenta);
        rectangle.setFillColor(sf::Color:: Yellow);         
        if (circle.getGlobalBounds().findIntersection(rectangle.getGlobalBounds())) {

            // set color to indate interaction 
            circle.setFillColor(sf::Color::Red);
            rectangle.setFillColor(sf::Color::Red); 

        }


        window.clear();
        window.draw(circle);
        window.draw(rectangle); 
        window.display();
    }
}
