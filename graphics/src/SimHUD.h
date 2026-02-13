#pragma once 
#include<SFML/Graphics.hpp> 

class SimHUD {
    public: 
        bool loadFont(const std::string& path);                                     // load font for HUD 
        void setOffset(sf::Vector2f offset);                                        // offset from top-left of view 
        void update(int residents, int mutants, int step, float stepInterval, bool running);                                                              // for updating the information in the HUD 
        void drawHUD(sf::RenderWindow& window);                                     // draws the HUD to the window (positions relative to current view)

    private: 
        void positionElements(sf::Vector2f topLeft);                                // positions all elements relative to a top-left corner
        
        sf::Font font;                                                              // the font 
        std::optional<sf::Text> text;   // <-- change here
        sf::RectangleShape panel; 
        sf::RectangleShape barBack; 
        sf::RectangleShape barResidents; 
        sf::RectangleShape barMutants; 

        float barWidth = 220.0f; 
        float barHeight = 14.0f; 
        float residentBarWidth = 220.0f;                                            // current width of resident portion (for positioning mutant bar)
        sf::Vector2f offset{15.0f, 15.0f};                                          // offset from top-left of view

};