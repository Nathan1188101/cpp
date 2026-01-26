#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Test");
    sf::CircleShape circle(80.f);
    float x = 0.0f; 
    float y = 0.0f; 


    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        x++; 
        //y++;
        if (x == 10.0) {
            x = 10.0; 
        }
        circle.setPosition({x, y});

        window.clear();
        window.draw(circle);
        window.display();
    }
}
