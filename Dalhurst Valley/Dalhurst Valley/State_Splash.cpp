#include <SFML\Graphics.hpp>
#include "State_Splash.h"
#include <SFML/Audio.hpp>
#include "common.h"
#include "Menu3.h"
#include "Menu2.h"
#include <iostream>


State_Splash::State_Splash()
{

	music.openFromFile("assets/sounds/splash_screen_cut.ogg");
	music.setVolume(20);
	music.setLoop(true);

	viewer = new StaticViewer(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080));


	hero = new Hero();

	hud = new HUD();

	menu = new Menu3(880, 540, 400, "PLAY", "ABOUT", "EXIT");
	quitMenu = new Menu2(900, 280, 300, "YES", "NO");


	displayAbout = false;
	displayPlay = false;
	displayQuit = false;

	texLogo.loadFromFile("assets/images/logo.png");

	sprLogo.setTexture(texLogo);
	sprLogo.setPosition(560, 150);

	texAbout.loadFromFile("assets/images/about.png");
	sprAbout.setTexture(texAbout);

	texQuit.loadFromFile("assets/images/quit.png");
	sprQuit.setTexture(texQuit);

	texPlay.loadFromFile("assets/images/play.png");
	sprPlay.setTexture(texPlay);

	texBackground[0].loadFromFile("assets/images/splash_1.jpg");
	texBackground[1].loadFromFile("assets/images/splash_2.jpg");
	texBackground[2].loadFromFile("assets/images/splash_3.jpg");

	sprBackground[0].setTexture(texBackground[0]);
	sprBackground[1].setTexture(texBackground[1]);
	sprBackground[2].setTexture(texBackground[2]);

	i = 0;
	alpha1 = 0;
	alpha2 = 0;

	font.loadFromFile("assets/fonts/Sansation_Bold.ttf");
	name.setFont(font);
	name.setCharacterSize(85);
}


State_Splash::~State_Splash()
{

}

void State_Splash::handle_events()
{

	if (!displayAbout && !displayQuit && !displayPlay)
	{
		sf::Event eventSplash;
		while (window.pollEvent(eventSplash))
		{
			switch (eventSplash.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (eventSplash.key.code)
				{
				case sf::Keyboard::Up:
					menu->MoveUp();
					break;
				case sf::Keyboard::Down:
					menu->MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu->getPressedItem())
					{
					case 0:
						displayPlay = true;
						break;
					case 1:
						displayAbout = true;
						break;
					case 2:
						displayQuit = true;
						break;
					}
				}
			}
		}
	}

	if (displayAbout)
	{
		sf::Event eventAbout;
		while (window.pollEvent(eventAbout))
		{
			switch (eventAbout.type)
			{
			case sf::Event::KeyPressed:
				switch (eventAbout.key.code)
				{
				case sf::Keyboard::Space:
					displayAbout = false;
					break;
				}
			}
		}
	}

	if (displayQuit)
	{
		sf::Event eventQuit;
		while (window.pollEvent(eventQuit))
		{
			switch (eventQuit.type)
			{
			case sf::Event::KeyPressed:
				switch (eventQuit.key.code)
				{
				case sf::Keyboard::Up:
					quitMenu->MoveUp();
					break;
				case sf::Keyboard::Down:
					quitMenu->MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (quitMenu->getPressedItem())
					{
					case 0:
						exit_game();
						break;
					case 1:
						displayQuit = false;
						break;
					}
				}
			}
		}
	}

	if (displayPlay)
	{
		sf::Event eventPlay;
		while (window.pollEvent(eventPlay))
		{
			switch (eventPlay.type)
			{
			case sf::Event::TextEntered:
				if (eventPlay.text.unicode != 8)
					input += (char)eventPlay.text.unicode;
				else
					input = input.substr(0, input.length() - 1);
			case sf::Event::KeyPressed:
				switch (eventPlay.key.code)
				{
				case sf::Keyboard::Escape:
					displayPlay = false;
					break;
				case sf::Keyboard::Return:
					hero->setName(input);
					set_next_next_state(LEVEL_1);
					break;
				}
			}
		}
	}

}

void State_Splash::init_state()
{
	if (initState)
	{
		music.play();
		clock.restart();
		viewer->setView();
		initState = false;
	}
}


void State_Splash::logic()
{

}

void State_Splash::render()
{

	sf::Time time = clock.getElapsedTime();
	sprBackground[i].setColor(sf::Color(255, 255, 255, 255));
	sprBackground[(i + 1) % 3].setColor(sf::Color(255, 255, 255, 0));

	if (time.asSeconds() <= 3)
	{
		window.draw(sprBackground[i]);
	}
	if (time.asSeconds() > 3 && time.asSeconds() <= 3.5)
	{
		alpha1 = (3.5 - time.asSeconds()) * 255 / 0.5;
		alpha2 = 255 - alpha1;
		sprBackground[i].setColor(sf::Color(255, 255, 255, alpha1));
		sprBackground[(i + 1) % 3].setColor(sf::Color(255, 255, 255, alpha2));
		window.draw(sprBackground[i]);
		window.draw(sprBackground[(i + 1) % 3]);
	}
	if (time.asSeconds() > 3.5)
	{
		sprBackground[(i + 1) % 3].setColor(sf::Color(255, 255, 255, 255));
		window.draw(sprBackground[(i + 1) % 3]);
		i = (i + 1) % 3;
		clock.restart().asSeconds();
	}

	window.draw(sprLogo);

	menu->draw(window);

	if (displayAbout)
		window.draw(sprAbout);

	if (displayQuit)
	{
		window.draw(sprQuit);
		quitMenu->draw(window);
	}

	if (displayPlay)
	{
		name.setString(input);
		sf::FloatRect txtBounds = name.getLocalBounds();
		name.setPosition(960 - txtBounds.width / 2, 540 - txtBounds.height / 2);
		window.draw(sprPlay);
		window.draw(name);
	}

}

