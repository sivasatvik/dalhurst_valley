#pragma once
#include "GameState.h"
#include "Menu3.h"
#include "StaticViewer.h"

class State_Pause :
	public GameState
{
private:
	StaticViewer *viewer;
	Menu3* menu;
public:
	State_Pause();
	~State_Pause();
	void init_state();
	void handle_events();
	void logic();
	void render();

};

