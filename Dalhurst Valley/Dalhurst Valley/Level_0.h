#pragma once
#include "GameState.h"
#include "MapGenerator.h"
#include "StaticViewer.h"

class Level_0 :
	public GameState
{
private:
	MapGenerator *map;
	StaticViewer *viewer;
	std::vector<sf::Vector2f> enemyPositions;

public:
	Level_0();
	~Level_0();
	void init_state();
	void handle_events();
	void logic();
	void render();
};

