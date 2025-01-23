#include "Map.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

Map::Map(const string& filename) : doorOpen(false) {
    
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erreur : Impossible de charger la carte depuis " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        layout.push_back(line);
    }

    file.close();

    
    loadTextures();

    
    const float tileSize = 50.f;
    for (size_t y = 0; y < layout.size(); ++y) {
        for (size_t x = 0; x < layout[y].size(); ++x) {
            char symbol = layout[y][x];
            if (symbol == '#') {
                RectangleShape wall(Vector2f(tileSize, tileSize));
                wall.setPosition(x * tileSize, y * tileSize);
                wall.setTexture(&wallTexture);
                walls.push_back(wall);
            }
            else if (symbol == 'D') { 
                door.setSize(Vector2f(tileSize, tileSize));
                door.setPosition(x * tileSize, y * tileSize);
                door.setTexture(&doorTexture);
            }
        }
    }
}

void Map::loadTextures() {
    if (!wallTexture.loadFromFile("wall.png")) {
        cerr << "Erreur : Impossible de charger la texture murale" << endl;
    }
    if (!floorTexture.loadFromFile("floor.png")) {
        cerr << "Erreur : Impossible de charger la texture du sol" << endl;
    }
    if (!doorTexture.loadFromFile("door.png")) {
        cerr << "Erreur : Impossible de charger la texture de la porte" << endl;
    }
}

void Map::draw(RenderWindow& window) {
    const float tileSize = 50.f;
    for (size_t y = 0; y < layout.size(); ++y) {
        for (size_t x = 0; x < layout[y].size(); ++x) {
            if (layout[y][x] == '.') {
                RectangleShape floor(Vector2f(tileSize, tileSize));
                floor.setPosition(x * tileSize, y * tileSize);
                floor.setTexture(&floorTexture);
                window.draw(floor);
            }
        }
    }

    
    for (const auto& wall : walls) {
        window.draw(wall);
    }

    
    if (!doorOpen) {
        window.draw(door);
    }
}

bool Map::checkCollision(const FloatRect& bounds) const {
    for (const auto& wall : walls) {
        if (wall.getGlobalBounds().intersects(bounds)) {
            return true;
        }
    }
    return false;
}

bool Map::checkDoorCollision(const FloatRect& bounds, Player& player) {
    if (door.getGlobalBounds().intersects(bounds) && !doorOpen) {
        if (player.getCleCollecter() > 0) {
            doorOpen = true;
            player.collectCle(); 
        }
        return true;
    }
    return false;
}

bool Map::isDoorOpen() const {
    return doorOpen;
}
