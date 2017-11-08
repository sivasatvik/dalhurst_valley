#include <SFML/Graphics.hpp>
#include "Level_3.h"
#include "common.h"



Level_3::Level_3()
{
	map = new MapGenerator();
	map->loadMap("assets/maps/prison_map.txt");

	viewer = new DynamicViewer();

	villagers0 = new SetOfVillagers(sf::Vector2f(300, 250), 0, 0);
	villagers1 = new SetOfVillagers(sf::Vector2f(2000, 250), 1, 1);
	villagers2 = new SetOfVillagers(sf::Vector2f(300, 1950), 0, 2);
	villagers3 = new SetOfVillagers(sf::Vector2f(2000, 1950), 0, 3);

	texture.loadFromFile("assets/images/without.png");
	sprite.setTexture(texture);
	sprite.setPosition(600, 1500);


}


Level_3::~Level_3()
{

}

void Level_3::init_state()
{
	if (initState)
	{
		hero->setSpawnPoint(sf::Vector2f(300, 1550));
		viewer->initViewer(sf::Vector2f(300, 1550));

		initState = false;
	}
}

void Level_3::handle_events()
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

void Level_3::logic()
{

	hero->update(map, enemyPositions);
	viewer->updateViewer();
	hud->updateHUD();
	villagers0->walkVillagers();
	villagers1->walkVillagers();
	villagers2->walkVillagers();
	villagers3->walkVillagers();

	if (hero->getPosition().x > 3000)
	{
		set_next_next_state(LEVEL_6);
	}

}

void Level_3::render()
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