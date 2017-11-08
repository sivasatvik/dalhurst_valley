#pragma once
#include "GameState.h"
#include "DynamicViewer.h"
#include "SetOfVillagers.h"
#include <SFML/Graphics.hpp>
#include "MapGenerator.h"

class Level_4 :
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

	sf::Thread *thread0;
	sf::Thread *thread1;
	sf::Thread *thread2;
	sf::Thread *thread3;

	sf::Texture texture;
	sf::Sprite sprite;


public:
	Level_4();
	~Level_4();
	void init_state();
	void handle_events();
	void logic();
	void render();
};

