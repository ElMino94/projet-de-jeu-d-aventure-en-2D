#include "ennemi.h"

class Ennemi : public Entity {

protected:

    CircleShape ennemi;

public:

    Ennemi(float radius, Color color, Vector2f startPosition) {
        ennemi.setRadius(radius);
        ennemi.setFillColor(color);
        ennemi.setOrigin(radius, radius);
        ennemi.setPosition(startPosition);
    }

    FloatRect getBounds() const {

        return ennemi.getGlobalBounds();

    }

    void draw(RenderWindow& window) override {

        window.draw(ennemi);

    }
};