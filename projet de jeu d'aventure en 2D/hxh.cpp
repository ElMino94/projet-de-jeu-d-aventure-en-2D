#include "HxH.h"

using namespace sf;

HxH::HxH(Vector2f startPosition) : Ennemi(20.f, Color::Red, startPosition), speed(100.f) {}

void HxH::maj(float deltaTime, const Vector2f& playerPosition, const Vector2u& windowSize) {
    Vector2f direction = playerPosition - ennemi.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }
    ennemi.move(direction * speed * deltaTime);
}
