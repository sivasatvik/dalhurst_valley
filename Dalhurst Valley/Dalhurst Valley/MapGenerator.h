#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>


class MapGenerator
{
private:
	sf::Texture tilesTexture;
	sf::Sprite tiles;
	std::vector<std::vector<sf::Vector2i>> map;
public:
	MapGenerator();
	~MapGenerator();
	void loadMap(char *filename);
	void drawMap();
	std::vector<std::vector<int>> cMap;

};

