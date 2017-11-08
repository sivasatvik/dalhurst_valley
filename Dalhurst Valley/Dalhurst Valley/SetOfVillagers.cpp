#include "SetOfVillagers.h"
#include "Villager.h"
#include <SFML/Graphics.hpp>


SetOfVillagers::SetOfVillagers(sf::Vector2f spawnPoint, int direction, int style)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			villagers[(3 * i) + j] = new Villager(sf::Vector2f(spawnPoint.x + j * 400, spawnPoint.y + i * 400), (direction + i + j) % 2, (style + i + j) % 4);
		}
	}

}


void SetOfVillagers::walkVillagers()
{
	for (int i = 0; i < 9; i++)
	{
		villagers[i]->walkAround();
	}
}

void SetOfVillagers::drawVillagers()
{
	for (int i = 0; i < 9; i++)
	{
		villagers[i]->drawVillager();
	}
}

SetOfVillagers::~SetOfVillagers()
{

}
