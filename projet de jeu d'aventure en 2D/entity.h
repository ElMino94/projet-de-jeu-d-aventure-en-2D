#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {
public:

    virtual void maj(float deltaTime, const Vector2u& windowSize) = 0;
    virtual void draw(RenderWindow& window) = 0;

};

#endif