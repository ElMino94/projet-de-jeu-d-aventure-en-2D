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
    Texture wallTexture;
    Texture floorTexture;
    Texture doorTexture;
    vector<RectangleShape> walls; 
    RectangleShape door;             
    bool doorOpen;

public:
    Map(const string& filename);
    void loadTextures();
    void draw(RenderWindow& window);
    bool checkCollision(const FloatRect& bounds) const;
    bool checkDoorCollision(const FloatRect& bounds, Player& player);
    bool isDoorOpen() const;
};

#endif
