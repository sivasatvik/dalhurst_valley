#pragma once

class GameState
{
public:
	virtual void init_state() = 0;
	virtual void handle_events() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~GameState() {};
};