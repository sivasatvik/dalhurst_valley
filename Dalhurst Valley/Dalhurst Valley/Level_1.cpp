#include <SFML/Graphics.hpp>
#include "Level_1.h"
#include "common.h"
#include "DynamicViewer.h"


Level_1::Level_1()
{
	map = new MapGenerator();
	enemy = new Enemy(sf::Vector2f(3300, 400));
	map->loadMap("assets/maps/map1.txt");
	enemy_spawn = false;
	enemy_dead = false;
	viewer = new DynamicViewer();
	allowHitting = true;
	i = 0;
}


Level_1::~Level_1()
{

}

void Level_1::init_state()
{
	if (initState)
	{
		hero->setSpawnPoint(sf::Vector2f(300, 2450));
		viewer->initViewer(sf::Vector2f(300, 2450));
		enemyThread = new sf::Thread(&Enemy::Update, enemy);
		initState = false;
	}
}

void Level_1::handle_events()
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
			case sf::Keyboard::Up:
				hero->resetOrientation();
			case sf::Keyboard::Down:
				hero->resetOrientation();
			case sf::Keyboard::Left:
				hero->resetOrientation();
			case sf::Keyboard::Right:
				hero->resetOrientation();
			}
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				pause_game();
				break;
			case sf::Keyboard::X:
				if (allowHitting) {
					if (enemy_spawn && enemy->getHealth() > 0)
						if (hero->hit(enemyPositions[0])) {
							enemy->getHit();
							if (enemy->getHealth() <= 0)
								enemy_dead = true;
							allowHitting = false;
						}

				}
					
			}
		}
	}
}

void Level_1::logic()
{
	if (allowHitting == false)
	{
		if (i < 45)
		{
			i++;
		}
		if (i >= 45)
		{
			i = 0;
			allowHitting = true;
		}
	}

	hero->update(map, enemyPositions);
	viewer->updateViewer();
	hud->updateHUD();

	if (!enemy_spawn && !enemy_dead) {
		sf::Vector2f current_point = hero->getPosition();
		if (current_point.x >= 3000) {
			enemy_spawn = true;
		}
	}

	else {
		if (enemy->getHealth() > 0) {
			enemyPositions.clear();
			enemy->map = map;
			enemyThread->launch();
			enemyPositions.push_back(enemy->getPosition());
		}
		else {
			if (enemy_dead) {
				hero->enemydefeat();
				enemy_dead = false;
			}
			enemyPositions.clear();
		}

	}


	if (hero->getPosition().x > 4800)
	{
		set_next_next_state(LEVEL_3);
	}
}

void Level_1::render()
{
	map->drawMap();
	hero->drawHero();
	if ((enemy_spawn == true && enemy->getHealth() > 0)) {
		enemy->drawEnemy();
	}
	
	hud->drawHUD();

}
