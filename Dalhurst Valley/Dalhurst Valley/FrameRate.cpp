#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include "FrameRate.h"
#include "common.h"




FrameRate::FrameRate()
{
	font.loadFromFile("assets/fonts/Forgott_Bold.ttf");

	txtFrate.setFont(font);
	txtFrate.setCharacterSize(15);
	txtFrate.setColor(sf::Color(255, 255, 255, 150));
	txtFrate.setCharacterSize(25);

	display_frate = 0;
}


FrameRate::~FrameRate()
{
}

void FrameRate::drawFrameRate()
{
	std::stringstream ss;
	ss.precision(4);
	ss << display_frate;
	txtFrate.setString("Frame Rate: " + ss.str() + " FPS");
	txtFrate.setPosition(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))));
	window.draw(txtFrate);

}


void FrameRate::calcFrameRate()
{
	sf::Time frTime = frClock.getElapsedTime();
	live_frate = 1.0f / frTime.asSeconds();
	frClock.restart().asSeconds();

}

void FrameRate::dispFrameRate()
{
	sf::Time dispTime = dispClock.getElapsedTime();
	if (dispTime.asSeconds() <= 0.25)
	{
		drawFrameRate();
	}
	if (dispTime.asSeconds() > 0.25)
	{
		drawFrameRate();
		display_frate = live_frate;
		dispClock.restart().asSeconds();
	}
}
