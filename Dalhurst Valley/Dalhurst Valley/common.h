#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Hero.h"
#include "HUD.h"
#include "states.h"

extern enum GameStates
{
	STATE_NULL,
	STATE_START,
	STATE_SPLASH,
	LEVEL_0, //Empty
	LEVEL_1, //1 Enemy
	LEVEL_2, //Respawn
	LEVEL_3, //NMT Prison
	LEVEL_4, //MT Prison
	LEVEL_5, //Bridge
	LEVEL_6, //Boss
	GAME_OVER,
	STATE_BLANK,
	STATE_EXIT
};


extern int currentStateID;
extern int nextStateID;
extern int nextNextStateID;

extern bool loadState;
extern bool initState;

extern GameState *currentState; 
extern GameState *pausedState;
extern GameState *nextState;
extern GameState *pauseState;

extern void set_next_next_state(int State);
extern void switch_state();
extern void load_state();
extern void pause_game();
extern void unpause_game();
extern void exit_game();

extern sf::RenderWindow window;

extern Hero *hero;

extern HUD *hud;