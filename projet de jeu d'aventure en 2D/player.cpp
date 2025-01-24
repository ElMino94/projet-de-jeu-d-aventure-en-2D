#include "Player.h"
#include <iostream>

using namespace sf;

Player::Player()
    :
    velocity(0.f, 0.f),
    speed(200.f),
    originalSpeed(200.f),
    boostDuration(0.f),
    clecollecter(0) {

    
    if (!texture.loadFromFile("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\asset\\player.png")) { 
        cerr << "Erreur : Impossible de charger la texture du joueur" << endl;
    }

    
    player.setTexture(texture);
    player.setPosition(position);
    player.setScale(0.7f, 0.7f);
}

void Player::loadTexture(const string& filename) {
    if (!texture.loadFromFile(filename)) {
        cerr << "Erreur : Impossible de charger la texture depuis " << filename << endl;
    }
    player.setTexture(texture);
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
    touche();
    position += velocity * deltaTime;

    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + player.getGlobalBounds().width > windowSize.x)
        position.x = windowSize.x - player.getGlobalBounds().width;
    if (position.y + player.getGlobalBounds().height > windowSize.y)
        position.y = windowSize.y - player.getGlobalBounds().height;

    player.setPosition(position);

    if (boostDuration > 0) {
        boostDuration -= deltaTime;
        if (boostDuration <= 0) {
            resetSpeed();
        }
    }
}

void Player::wallCol(const vector<Sprite>& walls) {

    for (const auto& wall : walls) {
        if (player.getGlobalBounds().intersects(wall.getGlobalBounds())) {

            FloatRect wallBounds = wall.getGlobalBounds();
            FloatRect playerBounds = player.getGlobalBounds();

            player.setPosition(position);
        }
    }

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

void Player::resetSpeed() {
    speed = originalSpeed;
    boostDuration = 0.f;
}

void Player::collectCle() {
    clecollecter++;
}

int Player::getCleCollecter() const {
    return clecollecter;
}

bool Player::BoostOn() const {
    return boostDuration > 0;
}
