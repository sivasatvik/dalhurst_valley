#pragma once
#include <SFML/Graphics.hpp>
#include "MapGenerator.h"
#include "GameState.h"
#include "DynamicViewer.h"
#include "SetOfVillagers.h"

class Level_3 :
	public GameState
{
private:
	MapGenerator *map;
	DynamicViewer *viewer;
	std::vector<sf::Vector2f>enemyPositions;
	SetOfVillagers *villagers0;
	SetOfVillagers *villagers1;
	SetOfVillagers *villagers2;
	SetOfVillagers *villagers3;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	Level_3();
	~Level_3();
	void init_state();
	void handle_events();
	void logic();
	void render();
};

