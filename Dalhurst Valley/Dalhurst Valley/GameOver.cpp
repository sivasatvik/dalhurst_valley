#include "GameOver.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "common.h"



GameOver::GameOver(int state)
{
	viewer = new StaticViewer(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080));

	font.loadFromFile("assets/fonts/Sansation_Bold.ttf");

	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(50);
	if (state == 0)
		text.setString("You died. Game Over. Press Space to Quit.");
	else
		text.setString("You defeated the Dragon. That's cool. Press Space to Quit.");
	sf::FloatRect txtBounds = text.getLocalBounds();

	text.setPosition(960 - txtBounds.width / 2, 540 - txtBounds.height / 2);

}


GameOver::~GameOver()
{
}

void GameOver::handle_events()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				window.close();
			}

		}
	}
}


void GameOver::logic()
{
	viewer->setView();

	//No logic in this state
}

void GameOver::render()
{
	window.draw(text);
}


void GameOver::init_state()
{
	if (initState)
	{
		initState = false;
	}
}