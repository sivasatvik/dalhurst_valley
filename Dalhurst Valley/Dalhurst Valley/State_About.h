#pragma once
#include "GameState.h"


class State_About :
	public GameState
{
private:
	sf::Font font;
	sf::Text txtAbout;


public:
	State_About();
	~State_About();
	void handle_events();
	void logic();
	void render();
};

