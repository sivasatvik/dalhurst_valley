#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "StaticViewer.h"

class GameOver :
	public GameState
{
private:
	StaticViewer *viewer;
	sf::Font font;
	sf::Text text;

public:
	GameOver(int state);
	~GameOver();
	void init_state();
	void handle_events();
	void logic();
	void render();
};

