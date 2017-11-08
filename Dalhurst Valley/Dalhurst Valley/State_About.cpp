#include <SFML/Graphics.hpp>
#include "State_About.h"
#include "common.h"



State_About::State_About()
{
	font.loadFromFile("assets/fonts/Comfortaa_Bold.ttf");

	txtAbout.setFont(font);
	txtAbout.setString("About: \n We the bitches, we do the shitz, press space to go back");
	txtAbout.setCharacterSize(50);
	sf::FloatRect txtBounds = txtAbout.getLocalBounds();
	txtAbout.setPosition(960 - txtBounds.width / 2, 540 - txtBounds.height / 2);
}


State_About::~State_About()
{
}

void State_About::handle_events()
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
				set_next_state(STATE_SPLASH);
			}

		}
	}
}

void State_About::logic()
{
	//No logic in this state
}

void State_About::render()
{

	window.draw(txtAbout);

}