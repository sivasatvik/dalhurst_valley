#pragma once
#include "Villager.h"
#include <SFML/Graphics.hpp>


class SetOfVillagers
{
private:
	Villager *villagers[9];
public:
	void walkVillagers();
	void drawVillagers();
	SetOfVillagers(sf::Vector2f spawnPoint, int direction, int style);
	~SetOfVillagers();
};

