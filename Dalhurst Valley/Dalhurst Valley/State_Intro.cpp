#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "State_Intro.h"
#include "common.h"



State_Intro::State_Intro()
{
	music.openFromFile("assets/sounds/splash_screen.ogg");
	music.setVolume(20);

	viewer = new StaticViewer(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080));

	font.loadFromFile("assets/fonts/Sansation_Bold.ttf");

	txtCourse.setFont(font);
	txtCourse.setString("CS2433: Principles of Programming Languages II");
	txtCourse.setCharacterSize(50);
	sf::FloatRect txtBounds = txtCourse.getLocalBounds();
	txtCourse.setPosition(960 - txtBounds.width / 2, 540 - txtBounds.height / 2);

	texLogo.loadFromFile("assets/images/logo.png");

	sprLogo.setTexture(texLogo);
	sprLogo.setPosition(560, 390);

	texBackground.loadFromFile("assets/images/splash_1.jpg");

	sprBackground.setTexture(texBackground);

}


State_Intro::~State_Intro()
{

}

void State_Intro::init_state()
{
	if (initState)
	{
		viewer->setView();
		initState = false;
	}
}

void State_Intro::handle_events()
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
				set_next_next_state(LEVEL_0);
			}

		}
	}
}

void State_Intro::logic()
{
	//No logic in this state
}

void State_Intro::render()
{
	sf::Time time = clock.getElapsedTime();

	sf::Time musicTime = musicClock.getElapsedTime();

	if (musicTime.asSeconds() > 4)
	{
		music.play();
		musicClock.restart().asSeconds();
	}

	int alpha = 0;
	if (time.asSeconds() > 0.5 && time.asSeconds() <= 1.5)
	{
		alpha = (time.asSeconds() - 0.5) * 255;
		txtCourse.setColor(sf::Color(255, 255, 255, alpha));
		window.draw(txtCourse);
	}

	alpha = 255;
	if (time.asSeconds() > 1.5 && time.asSeconds() <= 2.5)
	{
		txtCourse.setColor(sf::Color(255, 255, 255, alpha));
		window.draw(txtCourse);
	}

	if (time.asSeconds() > 2.5 && time.asSeconds() <= 3.5)
	{
		alpha = (3.5 - time.asSeconds()) * 255;
		txtCourse.setColor(sf::Color(255, 255, 255, alpha));
		window.draw(txtCourse);
	}

	if (time.asSeconds() > 4 && time.asSeconds() <= 5) {
		window.draw(sprLogo);
	}

	if (time.asSeconds() > 5 && time.asSeconds() <= 6.5) {
		float pos_y = 390 - 240 * (time.asSeconds() - 5) / 1.5;
		sprLogo.setPosition(560, pos_y);
		window.draw(sprLogo);
	}

	alpha = 0;
	if (time.asSeconds() > 6 && time.asSeconds() <= 7.5)
	{
		alpha = (time.asSeconds() - 6) * 255 / 1.5;
		sprBackground.setColor(sf::Color(255, 255, 255, alpha));
		window.draw(sprBackground);
	}

	



	if (time.asSeconds() > 7)
	{
		sprBackground.setColor(sf::Color(255, 255, 255, 255));
		window.draw(sprBackground);
		set_next_next_state(LEVEL_0);

	}
	if (time.asSeconds() > 6.5) {
		sprLogo.setPosition(560, 150);
		window.draw(sprLogo);
	}


}