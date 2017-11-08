#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "MapGenerator.h"
#include "DynamicViewer.h"
#include "Enemy.h"

class Level_1 :
	public GameState
{
private:
	Enemy *enemy;
	MapGenerator *map;
	DynamicViewer *viewer;
	bool enemy_spawn;
	bool enemy_dead;
	std::vector<sf::Vector2f>enemyPositions;
	sf::Thread *enemyThread;
	bool allowHitting;
	int i;

public:
	Level_1();
	~Level_1();
	void init_state();
	void handle_events();
	void logic();
	void render();
};

