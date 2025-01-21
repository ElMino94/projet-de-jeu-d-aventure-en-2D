#ifndef HXH_H
#define HXH_H

#include "Ennemi.h"

using namespace sf;

class HxH : public Ennemi {
private:
    float speed;

public:
    HxH(Vector2f startPosition);

    void maj(float deltaTime, const Vector2f& playerPosition, const Vector2u& windowSize);
    void maj(float deltaTime, const Vector2u& windowSize) override {}
};

#endif
