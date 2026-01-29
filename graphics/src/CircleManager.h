#include<SFML/Graphics.hpp>

class CircleManager {
    public: 
        void placeCircle(const sf::RenderWindow& window);
        void selectCircle(const sf::RenderWindow& window, sf::Vector2i mousePos);

    private:
        // members 
        float radius = 50.0f; 
        sf::CircleShape* selected = nullptr; // empty to start (nothing selected) 
        std::vector<std::unique_ptr<sf::CircleShape>> circles;

        // private functions
        bool isCircleClicked(const sf::RenderWindow& windowRef, sf::Vector2i mousePos, const sf::Vector2f& circlePos); // should be private memeber function because it's an internal selection check
            
};