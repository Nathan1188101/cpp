#include<SFML/Graphics.hpp>
#include<iostream> 
#include<cmath> 
#include<vector>
#include<random>

// -------------------- COOL BACKGROUND: STARFIELD --------------------
struct Starfield {
    sf::VertexArray stars;         // points
    sf::FloatRect worldBounds;     // where stars live in world coords

    Starfield(int count, sf::FloatRect bounds)
        : stars(sf::PrimitiveType::Points, count), worldBounds(bounds)
    {
        std::mt19937 rng(std::random_device{}());
        // making position and size (within a bound) random 
        std::uniform_real_distribution<float> xDist(bounds.position.x, bounds.position.x + bounds.size.x);
        std::uniform_real_distribution<float> yDist(bounds.position.y, bounds.position.y + bounds.size.y);

        for (std::size_t i = 0; i < stars.getVertexCount(); i++) {
            stars[i].position = { xDist(rng), yDist(rng) };

            // Different brightness for depth vibe (no extra textures needed)
            uint8_t brightness = static_cast<uint8_t>(150 + (i % 105)); // 150..254
            stars[i].color = sf::Color(brightness, brightness, brightness);
        }
    }

    void update(float dt, const sf::View& camera) {
        // gentle drift speed; tweak to taste
        const float speedX = -10.f;
        const float speedY = -3.f;

        // Keep stars within a moving "window" around the camera so you can travel forever
        sf::Vector2f camCenter = camera.getCenter();
        sf::Vector2f camSize   = camera.getSize();

        // Define a big box around the camera (bigger than the screen)
        // so new stars wrap in off-screen.
        float pad = 400.f;
        sf::FloatRect box(
            { camCenter.x - camSize.x / 2.f - pad, camCenter.y - camSize.y / 2.f - pad },
            { camSize.x + 2.f * pad,              camSize.y + 2.f * pad }
        );

        for (std::size_t i = 0; i < stars.getVertexCount(); i++) {
            stars[i].position.x += speedX * dt;
            stars[i].position.y += speedY * dt;

            // Wrap stars around the camera-centered box
            if (stars[i].position.x < box.position.x) stars[i].position.x = box.position.x + box.size.x;
            if (stars[i].position.x > box.position.x + box.size.x) stars[i].position.x = box.position.x;

            if (stars[i].position.y < box.position.y) stars[i].position.y = box.position.y + box.size.y;
            if (stars[i].position.y > box.position.y + box.size.y) stars[i].position.y = box.position.y;
        }
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(stars);
    }
};
// --------------------------------------------------------------------

struct Ball {
    sf::CircleShape circle; 
    sf::Vector2f velocity; 

    Ball(sf::Vector2f position, float radius) {
        circle.setPosition(position);
        circle.setRadius(radius); 
        circle.setOrigin(circle.getGeometricCenter()); 
        circle.setFillColor(sf::Color::White); 
        velocity = {0, 0};  
    }

    sf::Vector2f getPosition() {return circle.getPosition();}
    float getRadius() {return circle.getRadius();} 
    void setPosition(sf::Vector2f position) {circle.setPosition(position);}
    void move(sf::Vector2f offset) {circle.move(offset);}
    void draw(sf::RenderWindow& window) {window.draw(circle);} 
};

std::vector<Ball> balls; 
float gravity_strength = 20.0f;

void placeBall(const sf::RenderWindow& window) {

    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); 

    auto ball = Ball(worldPos, 20.0f);

    balls.push_back(ball);

}

void movement(sf::View& camera) {

        // move camera based on key input  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            camera.move({-2.f, 0}); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            camera.move({2.f, 0}); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            camera.move({0, -2.f}); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            camera.move({0, 2.f}); 
        }

}

int main() {

    sf::Clock frame_clock; 
    sf::Clock GlobalClock; 

    // setting up window 
    unsigned int width = 800; 
    unsigned int height = 600; 
    sf::RenderWindow window(sf::VideoMode({width, height}), "Main");
    window.setFramerateLimit(240);
    window.setKeyRepeatEnabled(false); 

    sf::View camera({width / 2.0f, height / 2.0f}, {800.0f, 600.0f});

    // -------------------- INIT BACKGROUND --------------------
    // Big initial bounds; after that, wrapping uses the camera box anyway
    Starfield starfield(500, sf::FloatRect({-2000.f, -2000.f}, {4000.f, 4000.f}));
    // ---------------------------------------------------------

    const float gravity = 500.0f; 

    while (window.isOpen()) {

        float dt = frame_clock.restart().asSeconds();
        float t = GlobalClock.getElapsedTime().asSeconds(); 

        while (auto ev = window.pollEvent()) {

            if (ev->is<sf::Event::Closed>()) {
                window.close(); 
            }

            if (const auto* scroll = ev->getIf<sf::Event::MouseWheelScrolled>()) {
                std::cout << "scrolling" << std::endl; 
                if (scroll->delta > 0) {
                    camera.zoom(0.9f);
                } else if (scroll->delta < 0) {
                    camera.zoom(1.1f);
                }
            }

            if (const auto* mouseMoved = ev->getIf<sf::Event::MouseMoved>()) {
                std::cout << "new mouse x: " << mouseMoved->position.x << std::endl; 
                std::cout << "new mouse y: " << mouseMoved->position.y << std::endl; 
            }

            if (const auto* key_pressed = ev->getIf<sf::Event::KeyPressed>()) {

                if (key_pressed->code == sf::Keyboard::Key::E) {
                    placeBall(window); 
                }

            }

        }

        sf::Vector2f top_left = {0.0, 0.0};
        sf::Vector2f bottom_right = {800.0, 600.0};
        sf::Vector2f top_right = {800.0, 0}; 
        sf::Vector2f bottom_left = {0, 600.0};
        sf::Vertex line[] = {
            {top_left}, {top_right}, {bottom_right}, {bottom_left}, {top_left}
        };

        for (auto& circle : balls) {
            
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            sf::Vector2f direction_vec = mousePos - circle.getPosition(); 
            float distance = std::sqrt(direction_vec.x * direction_vec.x + direction_vec.y * direction_vec.y); 
            sf::Vector2f push = {0, 0};
            if (distance > 0) {
                sf::Vector2f dir = direction_vec / distance; 
                push = dir * gravity_strength; 
                circle.velocity.y += gravity * dt; 
                circle.move(circle.velocity * dt); 
            } 

            float radius = circle.getRadius(); 
            sf::Vector2f cirlce_pos = circle.getPosition(); 
            if (cirlce_pos.y + radius > height) {
                cirlce_pos.y = height - radius; 
                circle.velocity.y *= -0.8f; 
                circle.setPosition(cirlce_pos); 
            }
            if (cirlce_pos.y - radius < 0) {
                cirlce_pos.y = 0 + radius; 
                circle.velocity.y *= -0.8f; 
                circle.setPosition(cirlce_pos);
            }

            if (cirlce_pos.x + radius > width) {
                cirlce_pos.x = width - radius; 
                circle.velocity.x *= -0.8f; 
                circle.setPosition(cirlce_pos); 
            } 
            if (cirlce_pos.x - radius < 0) {
                cirlce_pos.x = 0 + radius; 
                circle.velocity.x *= -0.8f; 
                circle.setPosition(cirlce_pos);  
            }

            if (distance <= radius * 2) {
                circle.velocity -= push; 
            }
        }

        // Move camera AFTER events, BEFORE drawing
        movement(camera);

        // Set the view before drawing world-space stuff (stars, balls, etc.)
        window.setView(camera); 

        // -------------------- DRAW BACKGROUND --------------------
        // Commenting out your color-changing background:
        /*
        sf::Color bg(
            50 + 50 * std::sin(t),
            20,
            100 + 50 * std::cos(t)
        );
        window.clear(bg);
        */
        window.clear(sf::Color::Black);

        // Update + draw starfield behind everything
        starfield.update(dt, camera);
        starfield.draw(window);
        // ---------------------------------------------------------

        window.draw(line, 5, sf::PrimitiveType::LineStrip);

        for(auto& circle : balls) {
            circle.draw(window);  
        }

        window.display();
    }
}
