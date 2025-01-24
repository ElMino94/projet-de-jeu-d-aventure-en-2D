#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H

#include "Player.h"

using namespace sf;

class Interaction {

public:
	
	virtual void interact(Player& player) = 0;
	virtual void draw(RenderWindow& window)  = 0;
	virtual const FloatRect getBounds() const = 0;

};

#endif