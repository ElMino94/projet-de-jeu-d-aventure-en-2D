#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;
using namespace sf;

class Map {
private:
    vector<string> layout;
    Texture wallTexture, floorTexture, doorTexture, keyTexture, playerTexture, patpatrouilleTexture, hxhTexture;
    vector<Sprite> walls;
    vector<Sprite> keys;
    Sprite door;
    Sprite patpatrouille;
    Sprite hxh;
    bool doorOpen;

public:

    Map(const string& filename);
    void loadTextures();
    void initializeSprites();
    void draw(RenderWindow& window);
    bool checkCollision(const FloatRect& bounds) const;
    Vector2f getPlayerStartPosition() const;
    const vector<Sprite>& getWalls() const;
    bool checkDoorCollision(const FloatRect& bounds, Player& player);
    bool isDoorOpen() const;
};

#endif
