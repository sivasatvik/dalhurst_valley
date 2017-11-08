#include "Villager.h"
#include "common.h"



Villager::Villager(sf::Vector2f spawnPoint, int direction, int skin)
{
	switch (skin)
	{
	case 0:
		texSheet.loadFromFile("assets/images/villager0.png");
		break;
	case 1:
		texSheet.loadFromFile("assets/images/villager1.png");
		break;
	case 2:
		texSheet.loadFromFile("assets/images/villager2.png");
		break;
	case 3:
		texSheet.loadFromFile("assets/images/villager3.png");
		break;
	}
	texSheet.loadFromFile("assets/images/villager0.png");
	sprSheet.setTexture(texSheet);
	source.x = 0;
	source.y = DOWN;
	speed = 1;
	newPos = spawnPoint;
	sprSheet.setPosition(spawnPoint);
	i = 0;
	wait_time = sf::microseconds(1500);

	dir = direction;
}

void Villager::orient(int direction)
{
	source.y = direction;
	sf::Time time = walkClock.getElapsedTime();
	if (time.asSeconds() > 0.2)
	{
		source.x = (source.x + 1) % 3;
		walkClock.restart().asSeconds();
	}
}

void Villager::drawVillager()
{
	sprSheet.setTextureRect(sf::IntRect(source.x * 100, source.y * 150, 100, 150));
	window.draw(sprSheet);
}

sf::Vector2f Villager::getPosition()
{
	sf::Vector2f position;
	position.x = (left + right) / 2;
	position.y = (top + bottom) / 2;
	return position;
}

void Villager::moveUp() 
{
	orient(UP);
	sprSheet.setPosition(sprSheet.getPosition().x, sprSheet.getPosition().y - speed);
}

void Villager::moveRight() 
{
	orient(RIGHT);
	sprSheet.setPosition(sprSheet.getPosition().x + speed, sprSheet.getPosition().y);

}

void Villager::moveLeft() 
{
	orient(LEFT);
	sprSheet.setPosition(sprSheet.getPosition().x - speed, sprSheet.getPosition().y);

}

void Villager::moveDown() 
{
	orient(DOWN);
	sprSheet.setPosition(sprSheet.getPosition().x, sprSheet.getPosition().y + speed);
}


void Villager::walkAround()
{
		if (i >= 0 && i < 99)
		{
			if (dir == 0)
				moveRight();
			else
				moveUp();
			i++;
		}
		if (i >= 99 && i < 297)
		{
			if (dir == 0)
				moveLeft();
			else
				moveDown();
			i++;
		}
		sf::sleep(wait_time);
		if (i >= 297 && i < 396)
		{
			if (dir == 0)
				moveRight();
			else
				moveUp();
			i++;
		}
		if (i == 396)
			i = 0;

}

Villager::~Villager()
{
}
