#include "Level_2.h"
#include <SFML/Graphics.hpp>
#include "common.h"
#include "DynamicViewer.h"


Level_2::Level_2()
{
	map = new MapGenerator();
	map->loadMap("assets/maps/map2.txt");
	viewer = new DynamicViewer();
	for (int i = 0; i < 4; i++) {
		enemy_spawn[i] = 0;
		enemy_dead[i] = 0;
	}
	enemy0 = new Enemy(sf::Vector2f(800, 800));
	enemy1 = new Enemy(sf::Vector2f(800, 1500));
	enemy2 = new Enemy(sf::Vector2f(1700, 900));
	enemy3 = new Enemy(sf::Vector2f(1700, 1400));

	thread0 = new sf::Thread(&Enemy::Update, enemy0);
	thread1 = new sf::Thread(&Enemy::Update, enemy1);
	thread2 = new sf::Thread(&Enemy::Update, enemy2);
	thread3 = new sf::Thread(&Enemy::Update, enemy3);
	death_counter = 0;
	i = 0;
	allowHitting = true;
}


Level_2::~Level_2()
{
}

void Level_2::init_state()
{
	if (initState)
	{
		hero->setSpawnPoint(sf::Vector2f(200, 1050));
		viewer->initViewer(sf::Vector2f(200, 1050));
		initState = false;
	}
}

void Level_2::handle_events()
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
				if (allowHitting)
				{
					if (enemy_spawn[0] && enemy0->getHealth() > 0)
						if (hero->hit(enemyPositions[0]))
						{
							enemy0->getHit();
							//if (enemy0->getHealth() <= 0)
							//	enemy_dead[0] = true;
						}
					if (enemy_spawn[1] && enemy1->getHealth() > 0)
						if (hero->hit(enemyPositions[1]))
						{
							enemy1->getHit();
						//	if (enemy1->getHealth() <= 0)
						//		enemy_dead[1] = true;
						}
					if (enemy_spawn[2] && enemy2->getHealth() > 0)
						if (hero->hit(enemyPositions[2]))
						{
							enemy2->getHit();
							//if (enemy2->getHealth() <= 0)
							//	enemy_dead[2] = true;
						}
					if (enemy_spawn[3] && enemy3->getHealth() > 0)
						if (hero->hit(enemyPositions[3]))
						{
							enemy3->getHit();
							//if (enemy3->getHealth() <= 0)
							//	enemy_dead[3] = true;
						}
					allowHitting = false;
					break;
				}
				

			}
		}
	}
}

void Level_2::logic()
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
	if (hero->getPosition().x > 2300)
	{
		set_next_next_state(LEVEL_4);
	}
	for (int i = 0; i < 4; i++) {
		if (!enemy_spawn[i] && !enemy_dead[i]) {
			sf::Vector2f current_point = hero->getPosition();
			if (current_point.x >= 1200) {
				enemy_spawn[i] = true;
			}
		}
	}
	enemyPositions.clear();
	if (enemy_spawn[0] && !enemy_dead[0]) {
		if (enemy0->getHealth() > 0) {
			enemy0->map = map;
			thread0->launch();
			enemyPositions.push_back(enemy0->getPosition());
		}
		else {
			//if (enemy_dead[0])
			//{
				hero->enemydefeat();
				enemy_dead[0] = false;
			//}
			delete enemy0;
			enemy0 = new Enemy(sf::Vector2f(800, 800));
			thread0 = new sf::Thread(&Enemy::Update, enemy0);
			enemyPositions.push_back(enemy0->getPosition());
		}
	}
	if (enemy_spawn[1] && !enemy_dead[1]) {
		if (enemy1->getHealth() > 0) {
			enemy1->map = map;
			thread1->launch();
			enemyPositions.push_back(enemy1->getPosition());
		}
		else {
			//if (enemy_dead[1])
			//{
				hero->enemydefeat();
				enemy_dead[1] = false;
			//}
			delete enemy1;
			enemy1 = new Enemy(sf::Vector2f(800, 1500));
			thread1 = new sf::Thread(&Enemy::Update, enemy1);
			enemyPositions.push_back(enemy1->getPosition());
		}
	}
	if (enemy_spawn[2] && !enemy_dead[2]) {
		if (enemy2->getHealth() > 0) {
			enemy2->map = map;
			thread2->launch();
			enemyPositions.push_back(enemy2->getPosition());
		}
		else {
			//if (enemy_dead[2])
			//{
				hero->enemydefeat();
				enemy_dead[2] = false;
			//}
			delete enemy2;
			enemy2 = new Enemy(sf::Vector2f(1700, 900));
			thread2 = new sf::Thread(&Enemy::Update, enemy2);
			enemyPositions.push_back(enemy2->getPosition());
		}
	}
	if (enemy_spawn[3] && !enemy_dead[3]) {
		if (enemy3->getHealth() > 0) {
			enemy3->map = map;
			thread3->launch();
			enemyPositions.push_back(enemy3->getPosition());
		}
		else {
			//if (enemy_dead[3])
			//{
				hero->enemydefeat();
				enemy_dead[3] = false;
			//}
			delete enemy3;
			enemy3 = new Enemy(sf::Vector2f(1700, 1400));
			thread3 = new sf::Thread(&Enemy::Update, enemy3);
			enemyPositions.push_back(enemy3->getPosition());
		}
	}
	
}

void Level_2::render()
{
	map->drawMap();

	hero->drawHero();

	if ((enemy_spawn[0] == true && enemy0->getHealth() > 0)) {
		enemy0->drawEnemy();
	}
	if ((enemy_spawn[1] == true && enemy1->getHealth() > 0)) {
		enemy1->drawEnemy();
	}
	if ((enemy_spawn[2] == true && enemy2->getHealth() > 0)) {
		enemy2->drawEnemy();
	}
	if ((enemy_spawn[3] == true && enemy3->getHealth() > 0)) {
		enemy3->drawEnemy();
	}
	hud->drawHUD();

}