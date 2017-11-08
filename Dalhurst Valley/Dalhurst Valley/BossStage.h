#pragma once
#include "GameState.h"
#include "MapGenerator.h"
#include "StaticViewer.h"
#include "Dragon.h"

class BossStage :
	public GameState
{
	MapGenerator *map;
	Dragon *dragon;
	StaticViewer *viewer;
	std::vector<sf::Vector2f>enemypositions;
	sf::Vector2f bossposition;
	bool boss_dead;
	bool allowHitting;
	int i;
	
public:
	BossStage();
	~BossStage();
	void init_state();
	void handle_events();
	void logic();
	void render();
};

