#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Test");
    sf::CircleShape circle(80.f);
    circle.setPosition({0.f, 0.f});

    for (int i = 0; i < 600; i++) {

    }


    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(circle);
        window.display();
    }
}
