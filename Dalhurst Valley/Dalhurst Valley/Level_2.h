#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "MapGenerator.h"
#include "DynamicViewer.h"
#include "Enemy.h"



class Level_2 :
	public GameState
{
private:
	MapGenerator *map;
	DynamicViewer *viewer;
	std::vector<sf::Vector2f>enemyPositions;
	Enemy *enemy0;
	Enemy *enemy1;
	Enemy *enemy2;
	Enemy *enemy3;

	sf::Thread *thread0;
	sf::Thread *thread1;
	sf::Thread *thread2;
	sf::Thread *thread3;

	bool enemy_spawn[4];
	bool enemy_dead[4];
	bool allowHitting;
	int death_counter;

	int i, j;
public:
	Level_2();
	~Level_2();
	void init_state();
	void handle_events();
	void logic();
	void render();
};