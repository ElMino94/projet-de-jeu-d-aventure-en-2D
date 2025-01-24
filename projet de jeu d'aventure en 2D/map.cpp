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
            else if (symbol == 'E') { // Ennemi type HxH
                ennemis.push_back(new HxH(Vector2f(x * tileSize, y * tileSize)));
            }
            else if (symbol == 'I') { // Potion
                potions.push_back(Potion(Vector2f(x * tileSize, y * tileSize)));
            }
            else if (symbol == 'Y') { // Ennemi type patpatrouille
                vector<Vector2f> waypoints = {
                    Vector2f(x * tileSize, y * tileSize),
                    Vector2f((x + 2) * tileSize, (y + 1) * tileSize),
                    Vector2f((x + 3) * tileSize, y * tileSize)
                };
                ennemis.push_back(new patpatrouille(Vector2f(x * tileSize, y * tileSize), waypoints));
            }
        }
    }
}

void Map::updateEnemies(float deltaTime, const Vector2f& playerPosition, const Vector2u& windowSize) {
    for (auto& ennemi : ennemis) {
        if (auto hxH = dynamic_cast<HxH*>(ennemi)) {
            hxH->maj(deltaTime, playerPosition, windowSize);
        }
        else if (auto patrouille = dynamic_cast<patpatrouille*>(ennemi)) {
            patrouille->maj(deltaTime, windowSize);
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

    for (const auto& ennemi : ennemis) {
        ennemi->draw(window);
    }

    // Dessiner les potions
    for (const auto& potion : potions) {
        window.draw(potion);
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
