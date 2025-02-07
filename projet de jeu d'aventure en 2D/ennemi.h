#ifndef ENNEMI_H
#define ENNEMI_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Ennemi : public Entity {
protected:
    CircleShape ennemi;

public:
    Ennemi(float radius, Color color, Vector2f startPosition);

    FloatRect getBounds() const;
    void draw(RenderWindow& window) override;
};

#endif
