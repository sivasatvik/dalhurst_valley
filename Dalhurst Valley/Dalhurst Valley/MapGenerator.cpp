#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include "MapGenerator.h"
#include "common.h"



MapGenerator::MapGenerator()
{
}


MapGenerator::~MapGenerator()
{
}


void MapGenerator::loadMap(char *filename)
{
	std::ifstream openmap;
	openmap.open(filename);
	std::vector<sf::Vector2i> tempMap;
	std::vector<int> tempcMap;
	map.clear();
	cMap.clear();
	if (!openmap) {
		std::cout << "nope";
	}

	if (openmap.is_open())
	{
		std::string tileLocation;
		openmap >> tileLocation;
		tilesTexture.loadFromFile(tileLocation);
		while (!openmap.eof())
		{
			std::string str, value;
			std::getline(openmap, str);
			std::stringstream stream(str);

			while (std::getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					std::string xx = value.substr(0, value.find(','));
					std::string yy = value.substr(value.find(',') + 1, value.find('-') - 2);
					std::string collider = value.substr(value.find('-') + 1);
					int a, x, y, i, j;
					for (i = 0; i < xx.length(); i++)
					{
						if (!isdigit(xx[i]))
							break;
					}

					for (j = 0; j < yy.length(); j++)
					{
						if (!isdigit(yy[j]))
							break;
					}

					x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
					y = (j == yy.length()) ? atoi(yy.c_str()) : -1;

					a = atoi(collider.c_str());

					tempMap.push_back(sf::Vector2i(x, y));
					tempcMap.push_back(a);

				}
			}
			cMap.push_back(tempcMap);
			tempcMap.clear();
			if (tempMap.size() > 0)
			{
				map.push_back(tempMap);
				tempMap.clear();
			}
		}
	}
	tiles.setTexture(tilesTexture);
	openmap.close();
}


void MapGenerator::drawMap()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].x != -1 && map[i][j].y != -1)
			{
				tiles.setPosition(j * 100, i * 100);
				tiles.setTextureRect(sf::IntRect(map[i][j].x  * 100, map[i][j].y * 100, 100, 100));
				window.draw(tiles);
			}
		}
	}
}

