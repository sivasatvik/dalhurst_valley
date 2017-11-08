#include <SFML/Graphics.hpp>
#include "Level_0.h"
#include "MapGenerator.h"
#include "common.h"



Level_0::Level_0()
{
	enemyPositions = {};

	map = new MapGenerator();
	map->loadMap("assets/maps/map0.txt");
	viewer = new StaticViewer(sf::Vector2f(950, 500), sf::Vector2f(1920, 1080));
}


Level_0::~Level_0()
{
}


void Level_0::init_state()
{
	if (initState)
	{
		hud->setName();
		hero->setSpawnPoint(sf::Vector2f(900, 450));
		viewer->setView();
		initState = false;
	}
}

void Level_0::handle_events()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				pause_game();
				break;

			}

		}
	}
}

void Level_0::logic()
{
	hero->update(map, enemyPositions);
	if (hero->getPosition().x > 1800)
	{
		set_next_next_state(LEVEL_2);
	}
	hud->updateHUD();
}

void Level_0::render()
{
	map->drawMap();
	hero->drawHero();
	hud->drawHUD();
}