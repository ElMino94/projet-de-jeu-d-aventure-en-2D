#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player : public Entity {
protected:

    CircleShape player;
    Vector2f velocity;
    float speed;
    float originalSpeed;
    float boostDuration;

public:

    Vector2f position;

    Player();

    void touche();
    void maj(float deltaTime, const Vector2u& windowSize) override;
    void draw(RenderWindow& window) override;
    FloatRect getBounds() const;
    void increaseSpeed(float boostAmount, float duration = 5.f);

};

#endif
