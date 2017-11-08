#pragma once
#include "GameState.h"
#include "common.h"
#include "Menu3.h"
#include "Menu2.h"
#include "StaticViewer.h"
#include <SFML/Audio.hpp>
#include <string>

class State_Splash :
	public GameState
{
private:
	StaticViewer *viewer;
	Menu3 *menu;
	Menu2 *quitMenu;
	sf::Texture texLogo, texBackground[3], texAbout, texQuit, texPlay;
	sf::Sprite sprLogo, sprBackground[3], sprAbout, sprQuit, sprPlay;
	sf::Clock clock;
	sf::Font font;
	sf::Text name;
	std::string input;
	int i;
	float alpha1, alpha2;
	sf::Music music;
	bool displayAbout;
	bool displayQuit;
	bool displayPlay;
public:
	State_Splash();
	~State_Splash();
	void init_state();
	void handle_events();
	void logic();
	void render();
};

