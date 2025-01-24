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
    Texture wallTexture, floorTexture, doorTexture, keyTexture,  treasureTexture;
    vector<Sprite> walls; 
    Sprite door;
    vector<Sprite> keys;
    vector<Sprite> treasures;
    bool doorOpen;

public:

    Map(const string& filename);
    void loadTextures();
    void initializeSprites();
    void draw(RenderWindow& window);
    bool checkCollision(const FloatRect& bounds) const;
    const vector<Sprite>& getWalls() const;
    bool checkDoorCollision(const FloatRect& bounds, Player& player);
    bool isDoorOpen() const;
};

#endif
