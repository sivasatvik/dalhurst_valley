#include "Enemy.h"
#include "common.h"
#include <iostream>


Enemy::Enemy(sf::Vector2f position)
{
	texSheet.loadFromFile("assets/images/baddie.png");
	sprSheet.setTexture(texSheet);
	source.x = 0;
	source.y = DOWN;
	speed = 10;
	health = 100;
	rectIn.setSize(sf::Vector2f(96, 8));
	rectIn.setFillColor(sf::Color::Red);
	rectOut.setSize(sf::Vector2f(100, 10));
	rectOut.setFillColor(sf::Color::Black);
	animateAttack = false;
	i = 0;
	j = 0;
	pauseAttack = false;

	sprSheet.setPosition(position);
	rectIn.setPosition(sf::Vector2f(position.x + 2, position.y + 2));
	rectOut.setPosition(position);
}


Enemy::~Enemy()
{
}




void Enemy::cycleAttack()
{
	if (animateAttack)
	{
		if (i >= 0 && i < 8)
		{
			source.x = 5;
			i++;
		}
		if (i >= 8 && i < 16)
		{
			source.x = 6;
			i++;
		}
		if (i >= 16 && i < 24)
		{
			source.x = 7;
			i++;
		}
		if (i >= 24 && i < 45)
		{
			source.x = 0;
			i++;
		}
		if (i >= 45)
		{
			i = 0;
			animateAttack = false;
		}
	}

}

void Enemy::orient(int direction)
{
	source.y = direction;
	sf::Time time = walkClock.getElapsedTime();
	if (time.asSeconds() > 0.15) {
		source.x = (source.x + 1) % 5;
		walkClock.restart().asSeconds();
	}
}

void Enemy::moveUp() {
	sprSheet.setPosition(sprSheet.getPosition().x, sprSheet.getPosition().y - speed);
	rectIn.setPosition(rectIn.getPosition().x, rectIn.getPosition().y - speed);
	rectOut.setPosition(rectOut.getPosition().x, rectOut.getPosition().y - speed);
}

void Enemy::moveRight() {
	sprSheet.setPosition(sprSheet.getPosition().x + speed, sprSheet.getPosition().y);
	rectIn.setPosition(rectIn.getPosition().x + speed, rectIn.getPosition().y);
	rectOut.setPosition(rectOut.getPosition().x + speed, rectOut.getPosition().y);
}

void Enemy::moveLeft() {
	sprSheet.setPosition(sprSheet.getPosition().x - speed, sprSheet.getPosition().y);
	rectIn.setPosition(rectIn.getPosition().x - speed, rectIn.getPosition().y);
	rectOut.setPosition(rectOut.getPosition().x - speed, rectOut.getPosition().y);

}

void Enemy::moveDown() {
	sprSheet.setPosition(sprSheet.getPosition().x, sprSheet.getPosition().y + speed);
	rectIn.setPosition(rectIn.getPosition().x, rectIn.getPosition().y + speed);
	rectOut.setPosition(rectOut.getPosition().x, rectOut.getPosition().y + speed);

}

void Enemy::drawEnemy() {
	sprSheet.setTextureRect(sf::IntRect(source.x * 100, source.y * 150, 100, 150));
	window.draw(rectOut);
	window.draw(rectIn);
	window.draw(sprSheet);
}

void Enemy::Update() 
{
	if (pauseAttack)
	{
		if (j < 45)
			j++;
		if (j >= 45)
		{
			j = 0;
			pauseAttack = false;
		}
	}

	sf::Vector2f oldpos = sprSheet.getPosition();
	sf::Vector2f heropos = hero->getPosition();
	cycleAttack();
	if (!animateAttack && !pauseAttack) {

		if (heropos.x - 25 < oldpos.x - 100)
		{
			orient(LEFT);
			moveLeft();
		}
		else if (heropos.y + 50 < oldpos.y)
		{
			orient(UP);
			moveUp();
		}
		else if (heropos.x - 50 > oldpos.x + 100)
		{
			orient(RIGHT);
			moveRight();
		}
		else if (heropos.y - 130 > oldpos.y + 150)
		{
			orient(DOWN);
			moveDown();
		}
		else
		{
			sf::Vector2f heropos = getPosition();
			sf::CircleShape heroCirc;
			heroCirc.setPosition(heropos);
			heroCirc.setRadius(60);
			sf::CircleShape enemyCirc;
			enemyCirc.setPosition(getPosition());
			enemyCirc.setRadius(60);
			if (sqrt(pow(heroCirc.getPosition().x - enemyCirc.getPosition().x, 2) +
				pow(heroCirc.getPosition().y - enemyCirc.getPosition().y, 2)) <=
				heroCirc.getRadius() + enemyCirc.getRadius())
			{
				pauseAttack = true;
				animateAttack = true;
				hero->getHit();
			}
		}
	}
		bottom = sprSheet.getPosition().y + 140;
		left = sprSheet.getPosition().x;
		right = sprSheet.getPosition().x + 90;
		top = sprSheet.getPosition().y + 50;

		tL.x = (int)left / 100; tL.y = ((int)top / 100) + 1;
		tR.x = ((int)right / 100); tR.y = ((int)top / 100) + 1;
		bL.x = (int)left / 100; bL.y = ((int)bottom / 100) + 1;
		bR.x = (int)right / 100; bR.y = ((int)bottom / 100) + 1;

		tiles.clear();

		tiles.push_back(tL);
		tiles.push_back(tR);
		tiles.push_back(bL);
		tiles.push_back(bR);
		for (int i = 0; i < tiles.size(); i++)
		{
			if (map->cMap[tiles[i].y][tiles[i].x] == 1)
			{
				sprSheet.setPosition(oldpos);
				oldpos.y -= 0;
				rectIn.setPosition(sf::Vector2f(oldpos.x + 2, oldpos.y + 2));
				rectOut.setPosition(oldpos);
				oldpos.y += 0;
			}
		}
	}




sf::Vector2f Enemy::getPosition() {
	sf::Vector2f position;
	position.x = (left + right) / 2;
	position.y = (top + bottom) / 2;
	return position;
}

void Enemy::getHit() {
	sf::Vector2f enemy_health = rectIn.getSize();
	enemy_health.x -= hero->getDamage();
	health -= hero->getDamage();
	if (enemy_health.x <= 0) {
		rectIn.setSize(sf::Vector2f(0, 0));
	}
	else {
		rectIn.setSize(enemy_health);
	}
}

int Enemy::getHealth() {
	return health;
}



