#include"cle.h"

using namespace sf;

Cle::Cle(Vector2f position) {

	cle.setSize(Vector2f(20.f, 20.f));
	cle.setFillColor(Color::Yellow);
	cle.setPosition(position);

}

void Cle::interact(Player& player) {

	player.collectCle();
	cle.setPosition(-100.f, -100.f);

}

void Cle::draw(RenderWindow& window) {

	window.draw(cle);

}

const FloatRect Cle::getBounds() const {

	return cle.getGlobalBounds();

}