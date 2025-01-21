#include "potion.h"

using namespace sf;

Potion::Potion(Vector2f position, float boost) : speedBoost(boost){

	potion.setRadius(15.f);
	potion.setFillColor(Color::Green);
	potion.setPosition(position);

}

void Potion::interact(Player& player) {

	player.increaseSpeed(speedBoost, 5.f);
	potion.setPosition(-100.f, -100.f); 

}

void Potion::draw(RenderWindow& window) {

	window.draw(potion);

}

const FloatRect Potion::getBounds() const {

	return potion.getGlobalBounds();

}