#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <memory>
using namespace std;




bool isColliding(sf::CircleShape& s, sf::Vector2f& vel, unsigned int w, unsigned int h) {
    sf::Vector2f s_pos = s.getPosition();
    float s_X = s_pos.x;
    float s_Y = s_pos.y;
    float radius = s.getRadius();

    bool collided = false; 

    // Check collision with left or right boundaries
    if (s_X - radius <= 0 || s_X + radius >= w) {
        vel.x = -vel.x; 
        collided = true;
    }

    // Check collision with top or bottom boundaries
    if (s_Y - radius <= 0 || s_Y + radius >= h) {
        vel.y = -vel.y; 
        collided = true;
    }

    return collided;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    unsigned int WIDTH = 640;
    unsigned int HEIGHT = 360;
    std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ WIDTH, HEIGHT }), "MAKING SHAPES");
    window->setFramerateLimit(60);

    sf::CircleShape circle(34.0f);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition(sf::Vector2f(
        (WIDTH / 2.0f) + static_cast<float>(rand() % 200 - 100), // Range: -100 to +100
        (HEIGHT / 2.0f) + static_cast<float>(rand() % 200 - 100) // Range: -100 to +100
    ));

    window->setMouseCursorVisible(true);
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineThickness(6.7f);
    circle.setOutlineColor(sf::Color::Magenta);
    circle.setPointCount(7);
    sf::Vector2f velocity(1.0f, -1.0f); // Ball velocity

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window->close();
                }
            }
        }

        // Render what is going on
        circle.rotate(sf::degrees(2));
        window->clear();

        bool collisionDect = isColliding(circle, velocity, WIDTH, HEIGHT);

        circle.move(velocity);
        window->draw(circle);


        window->display();
    }

    return 0;
}
