#include "PatPatrouille.h"

using namespace std;
using namespace sf;
patpatrouille::patpatrouille(Vector2f startPosition, vector<Vector2f> waypoints)
    : Ennemi(20.f, Color::Blue, startPosition), waypoints(waypoints), actpos(0), speed(80.f) {
}

void patpatrouille::maj(float deltaTime, const Vector2u& windowSize) {
    if (waypoints.empty()) return;

    Vector2f target = waypoints[actpos];
    Vector2f direction = target - ennemi.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }
    ennemi.move(direction * speed * deltaTime);

    if (length < 5.f) {
        actpos = (actpos + 1) % waypoints.size();
    }
}
