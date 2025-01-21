#include "Player.h"

using namespace sf;

Player::Player() : position(100.f, 100.f), velocity(0.f, 0.f), speed(200) {
    player.setRadius(50.f);
    player.setFillColor(Color::White);
    player.setPosition(position);
}

void Player::touche() {
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

void Player::maj(float deltaTime, const Vector2u& windowSize) {
    position += velocity * deltaTime;

    float radius = player.getRadius();
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + radius * 2 > windowSize.x) position.x = windowSize.x - radius * 2;
    if (position.y + radius * 2 > windowSize.y) position.y = windowSize.y - radius * 2;

    player.setPosition(position);
}

void Player::draw(RenderWindow& window) {
    window.draw(player);
}

FloatRect Player::getBounds() const {
    return player.getGlobalBounds();
}

void Player::increaseSpeed(float boostAmount, float duration) {

    speed += boostAmount;
    boostDuration = duration;
}
