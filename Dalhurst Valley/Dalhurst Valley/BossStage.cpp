#include <SFML/Graphics.hpp>
#include "BossStage.h"
#include "MapGenerator.h"
#include "common.h"



BossStage::BossStage()
{
	enemypositions = {};
	dragon = new Dragon(sf::Vector2f(800, 0));
	bossposition = dragon->getPosition();
	map = new MapGenerator();
	map->loadMap("assets/maps/map6.txt");
	viewer = new StaticViewer(sf::Vector2f(950, 500), sf::Vector2f(1920, 1080));
	boss_dead = 0;
	allowHitting = true;
	i = 0;
}


BossStage::~BossStage()
{
}

void BossStage::init_state() {
	if (initState) {
		hero->setSpawnPoint(sf::Vector2f(900, 750));
		viewer->setView();
		initState = false;
	}
}


void BossStage::handle_events() {
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
			case sf::Keyboard::X:
				if (allowHitting)
				{
				if (hero->hit_boss(bossposition)) {
					dragon->getHit();
					if (dragon->getHealth() <= 0) {
						boss_dead = true;
					}
					allowHitting = false;
				}
			}
			}

		}
	}
}


void BossStage::logic() {
	if(!boss_dead)
		dragon->Update();
	bossposition = dragon->getPosition();
	hero->update(map, enemypositions);
	
	//Should write the next level
	hud->updateHUD();

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

	if (dragon->getHealth() <= 0)
	{
		currentState = new GameOver(1);
	}
}

void BossStage::render() {
	map->drawMap();
	hero->drawHero();
	hud->drawHUD();
	if(!boss_dead)
		dragon->drawDragon();

}
