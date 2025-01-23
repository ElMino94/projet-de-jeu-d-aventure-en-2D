#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

class Map {


private:

	vector<vector<int>> grid;
	Texture wallTexture;
	Sprite wallSprite;
	int tileSize;

public:

	Map(const string& filename, const string& textureFile, int tileSize);
	void draw(RenderWindow& window);
	bool checkCollision(const FloatRect& playerBounds) const;

};





#endif