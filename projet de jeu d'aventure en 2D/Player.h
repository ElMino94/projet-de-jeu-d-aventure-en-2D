#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Player : public Entity {
protected:

    CircleShape player;
    Vector2f velocity;
    float speed;

public:

    Vector2f position;

    Player() : position(100.f, 100.f), velocity(0.f, 0.f), speed(200) {}

    void touche() {}

    void maj(float deltaTime, const Vector2u& windowSize) override {}

    void draw(RenderWindow& window) override {}

    FloatRect getBounds() const {}

};




#endif
