// Map.h
#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ennemi.h"
#include "Potion.h"
#include "Cle.h"
#include "HxH.h"
#include "PatPatrouille.h"

using namespace std;
using namespace sf;

class Map {
private:
    vector<string> layout;
    Texture wallTexture, floorTexture, doorTexture, keyTexture, playerTexture, ennemiTexture, potionTexture;
    vector<Sprite> walls;
    vector<Sprite> keys;
    vector<Ennemi*> ennemis; 
    vector<Potion> potions;
    vector<Cle> cles;
    Sprite door;
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
    void checkItemCollection(Player& player);
    void checkEnemyCollisions(Player& player);
    void updateEnemies(float deltaTime, const Vector2f& playerPosition, const Vector2u& windowSize);
};

#endif
