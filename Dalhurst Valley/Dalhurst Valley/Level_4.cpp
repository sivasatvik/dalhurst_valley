#include "Level_4.h"
#include "common.h"
#include "DynamicViewer.h"
#include <SFML/Graphics.hpp>

Level_4::Level_4()
{
	map = new MapGenerator();
	map->loadMap("assets/maps/prison_map.txt");

	viewer = new DynamicViewer();

	villagers0 = new SetOfVillagers(sf::Vector2f(300, 250), 0, 0);
	villagers1 = new SetOfVillagers(sf::Vector2f(2000, 250), 1, 1);
	villagers2 = new SetOfVillagers(sf::Vector2f(300, 1950), 0, 2);
	villagers3 = new SetOfVillagers(sf::Vector2f(2000, 1950), 0, 3);

	thread0 = new sf::Thread(&SetOfVillagers::walkVillagers, villagers0);
	thread1 = new sf::Thread(&SetOfVillagers::walkVillagers, villagers1);
	thread2 = new sf::Thread(&SetOfVillagers::walkVillagers, villagers2);
	thread3 = new sf::Thread(&SetOfVillagers::walkVillagers, villagers3);
	
	texture.loadFromFile("assets/images/with.png");
	sprite.setTexture(texture);
	sprite.setPosition(600, 1500);

}


void Level_4::init_state()
{
	if (initState)
	{
		hero->setSpawnPoint(sf::Vector2f(300, 1550));
		viewer->initViewer(sf::Vector2f(300, 1550));

		initState = false;

	
	}
}

void Level_4::handle_events()
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


void Level_4::logic()
{

	hero->update(map, enemyPositions);
	viewer->updateViewer();
	hud->updateHUD();
	thread0->launch();
	thread1->launch();
	thread2->launch();
	thread3->launch();

	if (hero->getPosition().x > 3000)
	{
		set_next_next_state(STATE_BLANK);
	}


}

Level_4::~Level_4()
{
}

void Level_4::render()
{
	map->drawMap();
	window.draw(sprite);
	hero->drawHero();
	villagers0->drawVillagers();
	villagers1->drawVillagers();
	villagers2->drawVillagers();
	villagers3->drawVillagers();
	hud->drawHUD();

}