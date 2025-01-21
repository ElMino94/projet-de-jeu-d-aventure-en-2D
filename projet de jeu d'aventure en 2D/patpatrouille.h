#ifndef PATPATROUILLE_H
#define PATPATROUILLE_H

#include "Ennemi.h"
#include <vector>

using namespace std;
using namespace sf;

class patpatrouille : public Ennemi {
private:
    vector<Vector2f> waypoints;
    int actpos;
    float speed;

public:
    patpatrouille(Vector2f startPosition, vector<Vector2f> waypoints);

    void maj(float deltaTime, const Vector2u& windowSize) override;
};

#endif
