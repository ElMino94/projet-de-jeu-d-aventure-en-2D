#include "Ennemi.h"

using namespace sf;

Ennemi::Ennemi(float radius, Color color, Vector2f startPosition) {
    ennemi.setRadius(radius);
    ennemi.setFillColor(color);
    ennemi.setOrigin(radius, radius);
    ennemi.setPosition(startPosition);
}

FloatRect Ennemi::getBounds() const {
    return ennemi.getGlobalBounds();
}

void Ennemi::draw(RenderWindow& window) {
    window.draw(ennemi);
}
