#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "GameState.h"
#include "FrameRate.h"
#include "states.h"
#include "common.h"

sf::Thread loaderThread(&load_state);



enum GameStates;

const char* stateStrings[] =
{
	"STATE_NULL",
	"STATE_START",
	"STATE_SPLASH",
	"LEVEL_0",
	"LEVEL_1",
	"LEVEL_2",
	"LEVEL_3",
	"LEVEL_4",
	"LEVEL_5",
	"LEVEL_6",
	"GAME_OVER",
	"STATE_BLANK",
	"STATE_EXIT"
};

const char* stateIdentifier(int enumVal)
{
	return stateStrings[enumVal];
}


int currentStateID = STATE_START;
int nextStateID = STATE_SPLASH;
int nextNextStateID = STATE_NULL;

bool loadState = true;
bool initState = true;

GameState *currentState = NULL;
GameState *nextState = NULL;


Hero *hero = NULL;
HUD *hud = NULL;

void set_next_next_state(int State)
{
	nextNextStateID = State;
}

void load_state()
{
	switch (nextStateID)
	{
	case STATE_SPLASH:
		nextState = new State_Splash();
		break;

	case LEVEL_0:
		nextState = new Level_0();
		break;

	case LEVEL_1:
		nextState = new Level_1();
		break;
	case LEVEL_2:
		nextState = new Level_2();
		break;
	case LEVEL_3:
		nextState = new Level_3();
		break;
	case LEVEL_4:
		nextState = new Level_4();
		break;
	case LEVEL_6:
		nextState = new BossStage();
		break;
	case STATE_BLANK:
		break;
	}
	std::cout << "Finished loading the state " << stateIdentifier(nextStateID) << " in the background." << std::endl;
}


void switch_state()
{
	if (nextNextStateID != STATE_NULL)
	{
		std::cout << "Call made to display next state!" << std::endl;
		loaderThread.wait();
		currentStateID = nextStateID;
		nextStateID = nextNextStateID;
		nextNextStateID = STATE_NULL;
		delete currentState;
		currentState = nextState;
		std::cout << "Just switched display to " << stateIdentifier(currentStateID) << std::endl;
		loadState = true;
		initState = true;
	}
}

//Functions and Variables to handle pausing and exiting the game

GameState *pausedState = NULL;
GameState *pauseState = new State_Pause();

void pause_game()
{
	initState = true;
	pausedState = currentState;
	currentState = pauseState;
}

void unpause_game()
{
	currentState = pausedState;
}

void exit_game()
{
	currentStateID = STATE_EXIT;
}



sf::RenderWindow window(sf::VideoMode(1920, 1080), "Dalhurst Valley", sf::Style::Fullscreen);


int main() {

	FrameRate *frameRate = new FrameRate();

	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	while (window.isOpen())
	{
		currentState = new State_Intro();
		while (currentStateID != STATE_EXIT)
		{
			switch_state();

			if (loadState)
			{
				loadState = false;
				std::cout << "Created new thread to load the state: " << stateIdentifier(nextStateID) << "." << std::endl;
				loaderThread.launch();
			}

			currentState->init_state();

			frameRate->calcFrameRate();

			currentState->handle_events();

			currentState->logic();

			window.clear();

			currentState->render();

			frameRate->dispFrameRate();

			window.display();
		}

		return 0;
	}

}