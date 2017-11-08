#pragma once

class FrameRate
{
private:
	float live_frate, display_frate;
	sf::Font font;
	sf::Text txtFrate;
	sf::Clock frClock;
	sf::Clock dispClock;

public:
	FrameRate();
	~FrameRate();
	void calcFrameRate();
	void drawFrameRate();
	void dispFrameRate();
};