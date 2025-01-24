#ifndef POTION_H
#define POTION_H

#include "Interaction.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Potion : public Interaction {
private:
    CircleShape potion;
    float speedBoost;

public:
    Potion(Vector2f position, float boost = 50.f);

    void interact(Player& player) override;
    void draw(RenderWindow& window) override; 
    const FloatRect getBounds() const override;
};


#endif