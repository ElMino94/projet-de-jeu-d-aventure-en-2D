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
    initializeSprites();

   
}

void Map::loadTextures() {

    if (!wallTexture.loadFromFile("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\asset\\wall.png")) {
        cerr << "Erreur : Impossible de charger la texture murale" << endl;
    }
    if (!floorTexture.loadFromFile("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\asset\\floor.png")) {
        cerr << "Erreur : Impossible de charger la texture du sol" << endl;
    }
    if (!doorTexture.loadFromFile("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\asset\\door1.png")) {
        cerr << "Erreur : Impossible de charger la texture de la porte" << endl;
    }
    if (!keyTexture.loadFromFile("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\asset\\key.png")) {
        cerr << "Erreur : Impossible de charger la texture de la clé" << endl;
    }
    if (!treasureTexture.loadFromFile("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\asset\\treasure.png")) {
        cerr << "Erreur : Impossible de charger la texture du trésor" << endl;
    }
    if (!playerTexture.loadFromFile("C:\\Users\\trestoux\\Documents\\GitHub\\projet-de-jeu-d-aventure-en-2D\\asset\\player.png")) {
        cerr << "Erreur : Impossible de charger la texture du trésor" << endl;
    }

}

void Map::initializeSprites() {
    const float tileSize = 50.f;
    for (size_t y = 0; y < layout.size(); ++y) {
        for (size_t x = 0; x < layout[y].size(); ++x) {
            char symbol = layout[y][x];
            Sprite sprite;

            if (symbol == '#') { 
                sprite.setTexture(wallTexture);
                sprite.setPosition(x * tileSize, y * tileSize);
                walls.push_back(sprite);
            }
            else if (symbol == '.') { 
                sprite.setTexture(floorTexture);
                sprite.setPosition(x * tileSize, y * tileSize);
            }
            else if (symbol == 'P') {
                sprite.setTexture(playerTexture);
                sprite.setPosition(x * tileSize, y * tileSize);
            }
            else if (symbol == 'D') { 
                door.setTexture(doorTexture);
                door.setPosition(x * tileSize, y * tileSize);
            }
            else if (symbol == 'K') { 
                sprite.setTexture(keyTexture);
                sprite.setPosition(x * tileSize, y * tileSize);
                keys.push_back(sprite);
            }

            /*else if (symbol == 'E') { 
                sprite.setTexture(enemyTexture);
                sprite.setPosition(x * tileSize, y * tileSize);
                enemies.push_back(sprite);
            }*/
            else if (symbol == 'T') { 
                sprite.setTexture(treasureTexture);
                sprite.setPosition(x * tileSize, y * tileSize);
                treasures.push_back(sprite);
            }
        }
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

    for (const auto& key : keys) {
        window.draw(key);
    }

    /*for (const auto& enemy : enemies) {
        window.draw(enemy);
    }*/

    for (const auto& treasure : treasures) {
        window.draw(treasure);
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

const vector<Sprite>& Map::getWalls() const {
    return walls;
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

Vector2f Map::getPlayerStartPosition() const {
    const float tileSize = 50.f; // La taille d'une tuile (ajuste selon ta configuration)
    for (size_t y = 0; y < layout.size(); ++y) {
        for (size_t x = 0; x < layout[y].size(); ++x) {
            if (layout[y][x] == 'P') { // Si on trouve le symbole 'P'
                return Vector2f(x * tileSize, y * tileSize); // Position en pixels
            }
        }
    }
    // Si aucun 'P' trouvé, retourne une position par défaut (exemple : coin supérieur gauche)
    return Vector2f(0.f, 0.f);
}


bool Map::isDoorOpen() const {
    return doorOpen;
}
