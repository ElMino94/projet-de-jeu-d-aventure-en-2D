#ifndef CLE_H
#define CLE_H

#include "interaction.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Cle : public Interaction {

private:

	RectangleShape cle;

public:

	Cle(Vector2f position);

	void interact(Player& player) override;
	void draw(RenderWindow& window) override;
	const FloatRect getBounds() const override;

};

#endif
