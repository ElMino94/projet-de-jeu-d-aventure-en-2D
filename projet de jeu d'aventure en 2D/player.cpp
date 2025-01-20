#include "Player.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

class Player : public Entity {
protected:

    CircleShape player;
    Vector2f velocity;
    float speed;

public:

    Vector2f position;

    Player() : position(100.f, 100.f), velocity(0.f, 0.f), speed(200) {
        player.setRadius(50.f);
        player.setFillColor(Color::White);
        player.setPosition(position);
    }

    void touche() {

        velocity = Vector2f(0.f, 0.f);

        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            velocity.y -= speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            velocity.y += speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            velocity.x -= speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            velocity.x += speed;
        }
    }

    void maj(float deltaTime, const Vector2u& windowSize) override {

        position += velocity * deltaTime;

        float radius = player.getRadius();
        if (position.x < 0) position.x = 0;
        if (position.y < 0) position.y = 0;
        if (position.x + radius * 2 > windowSize.x) position.x = windowSize.x - radius * 2;
        if (position.y + radius * 2 > windowSize.y) position.y = windowSize.y - radius * 2;

        player.setPosition(position);

    }

    void draw(RenderWindow& window) override {
        window.draw(player);
    }

    FloatRect getBounds() const {
        return player.getGlobalBounds();
    }

};


