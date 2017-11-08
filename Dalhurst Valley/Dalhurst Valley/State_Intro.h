#pragma once
#include "GameState.h"
#include <SFML/Audio.hpp>
#include "StaticViewer.h"

class State_Intro :
	public GameState
{
private:
	StaticViewer *viewer;
	sf::Font font;
	sf::Text txtCourse;
	sf::Texture texLogo, texBackground;
	sf::Sprite sprLogo, sprBackground;
	sf::Clock clock;
	sf::Clock musicClock;
	sf::Music music;

public:
	State_Intro();
	~State_Intro();
	void init_state();
	void handle_events();
	void logic();
	void render();
};

