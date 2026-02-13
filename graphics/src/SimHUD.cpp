#include"SimHUD.h" 
#include<SFML/Graphics.hpp> 
#include<string> 
#include<sstream> 

/// @brief for loading a font from a passed in path to the font 
/// @param path the path to the font 
bool SimHUD::loadFont(const std::string& path) {
    if (!font.openFromFile(path)) return false;

    text.emplace(font, "", 16); 
    text->setFillColor(sf::Color::White); 
    
    panel.setSize({280.0f, 135.0f}); 
    panel.setFillColor(sf::Color(0,0,0, 160)); 
    panel.setOutlineThickness(1.0f); 
    panel.setOutlineColor(sf::Color(255, 255, 255, 80)); 

    barBack.setSize({barWidth, barHeight});
    barBack.setFillColor(sf::Color(255, 255, 255, 30)); 

    barResidents.setFillColor(sf::Color::White);
    barMutants.setFillColor(sf::Color(255, 80, 80)); 

    return true; // font was loaded 
}

/// @brief set the offset from the top-left corner of the view
/// @param off the offset 
void SimHUD::setOffset(sf::Vector2f off) {
    offset = off;
}

/// @brief positions all HUD elements relative to a top-left corner
/// @param topLeft the top-left position to anchor to
void SimHUD::positionElements(sf::Vector2f topLeft) {
    sf::Vector2f position = topLeft + offset;
    panel.setPosition(position); 
    if (text) text->setPosition(position + sf::Vector2f(10.0f, 8.0f)); 

    barBack.setPosition(position + sf::Vector2f(10.0f, 105.0f)); 
    barResidents.setPosition(barBack.getPosition()); 
    barMutants.setPosition(barBack.getPosition() + sf::Vector2f(residentBarWidth, 0.0f)); 
}

void SimHUD::update(int residents, int mutants, int step, float stepInterval, bool running) {

    if (!text) return; // font not loaded so avoid updating 

    int population_size = residents + mutants;  
    float frac = (population_size > 0) ? (static_cast<float>(mutants) / population_size) : 0.0f; 
    
    // build HUD text 
    std::ostringstream ss; 
    ss << "Residents: " << residents << "\n"
       << "Mutants:   " << mutants << "\n"
       << "Mutant %:  " << static_cast<int>(frac * 100.0f + 0.5f) << "%\n"
       << "Step:      " << step << "\n"
       << "Tick:      " << stepInterval << "s  [" << (running ? "RUN" : "PAUSE") << "]";
    text->setString(ss.str());

    // ratio bar 
    float mutant_w = barWidth * frac; 
    residentBarWidth = barWidth - mutant_w; 

    barResidents.setSize({residentBarWidth, barHeight}); 
    barMutants.setSize({mutant_w, barHeight});

}

void SimHUD::drawHUD(sf::RenderWindow& window) {
    // Save current view, switch to default for fixed-size HUD
    sf::View savedView = window.getView();
    window.setView(window.getDefaultView());
    
    // Position elements at fixed screen coordinates
    positionElements({0.0f, 0.0f});
    
    window.draw(panel); 
    if (text) window.draw(*text); 
    window.draw(barBack); 
    window.draw(barResidents); 
    window.draw(barMutants); 
    
    // Restore camera view
    window.setView(savedView);
}

