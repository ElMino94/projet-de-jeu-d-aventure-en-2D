#include "Player.h"
#include "HxH.h"
#include "PatPatrouille.h"
#include "potion.h"
#include "cle.h"
#include "map.h"
#include <vector>
#include <memory>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

float calDist(const Vector2f& a, const Vector2f& b) {

    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

bool checkCollision(const FloatRect& a, const FloatRect& b) {

    return a.intersects(b);

}

Vector2f generatePosition(const Vector2u& windowSize, const Vector2f& referencePosition, float minDistance) {
    Vector2f position;
    do {
        position.x = static_cast<float>(rand() % windowSize.x);
        position.y = static_cast<float>(rand() % windowSize.y);
    } while (calDist(position, referencePosition) < minDistance);
    return position;
}

int main() {
    RenderWindow window(VideoMode(1500, 750), "Jeu d'aventure");
    window.setFramerateLimit(60);

    Player player;
    player.loadTexture("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\asset\\player.png");
    Clock clock;

    srand(static_cast<unsigned>(time(nullptr)));
    
    const float minSpDis = 150.f;

    Map map("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\map.txt");

    Vector2f playerStartPosition = map.getPlayerStartPosition();
    player.setPosition(playerStartPosition);
    Vector2f playerPosition = player.position;
    vector<unique_ptr<Ennemi>> ennemis;
    ennemis.push_back(make_unique<HxH>(generatePosition(window.getSize(), playerPosition, minSpDis)));
    ennemis.push_back(make_unique<patpatrouille>(generatePosition(window.getSize(), playerPosition, minSpDis), vector<Vector2f>{{700.f, 500.f}, { 700.f, 100.f }, { 100.f, 100.f }, { 100.f, 500.f }}));
         
    vector<unique_ptr<Interaction>> objets;
    objets.push_back(make_unique<Potion>(generatePosition(window.getSize(), playerPosition, minSpDis)));
    objets.push_back(make_unique<Cle>(generatePosition(window.getSize(), playerPosition, minSpDis)));


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        Vector2f previousPosition = player.position;
        player.maj(deltaTime, window.getSize());
        player.wallCol(map.getWalls(), previousPosition);

        if (map.checkCollision(player.getBounds())) {}

        map.checkDoorCollision(player.getBounds(), player);

        for (auto& ennemi : ennemis) {
            if (HxH* chaser = dynamic_cast<HxH*>(ennemi.get())) {
                chaser->maj(deltaTime, player.position, window.getSize());
            }
            else {
                ennemi->maj(deltaTime, window.getSize());
            }
        }

        for (auto it = objets.begin(); it != objets.end();) {
            if (checkCollision(player.getBounds(), (*it)->getBounds())) {
                (*it)->interact(player);
                it = objets.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto& ennemi : ennemis) {
            if (checkCollision(player.getBounds(), ennemi->getBounds())) {
                cout << "GAME OVER!!!!" << endl;
                return 0;
            }
        }

        window.clear();
        map.draw(window);
        player.draw(window);
        for (auto& ennemi : ennemis) {
            ennemi->draw(window);
        }
        for (auto& objet : objets) {
            objet->draw(window);
        }
        window.display();
    }

    return 0;
}
