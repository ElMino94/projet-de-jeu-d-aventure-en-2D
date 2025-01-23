#include "map.h"*

Map::Map(const string& filename, const string& textureFile, int tileSize) : tileSize(tileSize) {

	if (!wallTexture.loadFromFile(textureFile)) {
		cerr << "Erreur lors du chargement de la texuture des murs" << endl;
	}

	wallSprite.setTexture(wallTexture);

	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Erreur lors du chargement de la map" << endl;
	}

	string line;
	while (getline(file, line)) {
		vector<int> row;
		for (char c : line) {
			if (c == '1') {
				row.push_back(1);
			}
			else
			{
				row.push_back(0);
			}
		} 

		grid.push_back(row);
	}

	file.close();

}

void Map::draw(RenderWindow& window) {

	for (size_t y = 0; y < grid.size(); ++y)
	{
		for (size_t x = 0; x < grid[y].size(); ++x)
		{
			if (grid[y][x] == 1) {
				wallSprite.setPosition(x * tileSize, y * tileSize);
				window.draw(wallSprite);
			}
		}
	}
}

bool Map::checkCollision(const FloatRect& playerBounds) const {
	for (size_t y = 0; y < grid.size(); ++y) {
		for (size_t x = 0; x < grid[y].size(); ++x) {
			if (grid[y][x] == 1) {
				FloatRect wallBounds(x * tileSize, y * tileSize, tileSize, tileSize);
				if (playerBounds.intersects(wallBounds)) {
					return true;  
				}
			}
		}
	}
	return false;   
}