#include "Hero.h"
#include "common.h"
#include "MapGenerator.h"
#include <iostream>



Hero::Hero()
{
	texSheet.loadFromFile("assets/images/hero_sheet.png");
	sprSheet.setTexture(texSheet);
	source.x = 0;
	source.y = LEFT;
	speed = 10;
	level = 1;
	hp = 100;
	xp = 0;
	damage = DAMAGE[0];
	potions = 20;
	animateAttack = false;
	canConsumePotion = true;
	i = 0;
	j = 0;


}

void Hero::checkIfDead()
{
	if (hp < 0)
	{
		currentState = new GameOver(0);
	}
}

Hero::~Hero()
{

}

void Hero::checkLevelUp()
{
	while (level < 5) {
		if (xp > XP_TARGET[level - 1])
			levelUp();
		else
			return;
	}
}

void Hero::levelUp()
{
	level++;
 }


void Hero::resetOrientation()
{
	source.x = 0;
}


void Hero::setSpawnPoint(sf::Vector2f position)
{
	newPos = position;
	sprSheet.setPosition(position);
}

void Hero::setAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		animateAttack = true;
	}
}

void Hero::cycleAttack()
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

void Hero::orient(int direction)
{
	source.y = direction;
	sf::Time time = walkClock.getElapsedTime();
	if (time.asSeconds() > 0.07)
	{
		source.x = (source.x + 1) % 5;
		walkClock.restart().asSeconds();
	}
}


void Hero::drawHero()
{
	sprSheet.setTextureRect(sf::IntRect(source.x * 100, source.y * 150, 100, 150));
	window.draw(sprSheet);
}
float Hero::getDamage()
{
	return DAMAGE[level-1];
}


void Hero::update(MapGenerator *map, std::vector<sf::Vector2f> enemyposes)
{
	checkIfDead();
	if (!canConsumePotion)
	{
		if (j < 75)
			j++;
		if (j >= 75)
		{
			j = 0;
			canConsumePotion = true;
		}
	}

	consumePotion();
	setAttack();
	cycleAttack();
	if (!animateAttack)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			orient(UP);
			newPos.y -= speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			orient(LEFT);
			newPos.x -= speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			orient(DOWN);
			newPos.y += speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			orient(RIGHT);
			newPos.x += speed;
		}

		

}
	sf::Vector2f oldPos = sprSheet.getPosition();
	sprSheet.setPosition(newPos);

	bottom = sprSheet.getPosition().y + 140;
	left = sprSheet.getPosition().x + 10;
	right = sprSheet.getPosition().x + 90;
	top = sprSheet.getPosition().y + 60;

	sf::Vector2i tL(sf::Vector2i((int)left / 100, (int)top / 100 + 1));
	sf::Vector2i tR(sf::Vector2i((int)right / 100, (int)top / 100 + 1));
	sf::Vector2i bL(sf::Vector2i((int)left / 100, (int)bottom / 100 + 1));
	sf::Vector2i bR(sf::Vector2i((int)right / 100, (int)bottom / 100 + 1));

	tilesTouching.clear();

	tilesTouching.push_back(tL);
	tilesTouching.push_back(tR);
	tilesTouching.push_back(bL);
	tilesTouching.push_back(bR);


	for (int i = 0; i < tilesTouching.size(); i++)
	{
		if (map->cMap[tilesTouching[i].y][tilesTouching[i].x] == 1)
		{
			sprSheet.setPosition(oldPos);
			newPos = oldPos;
		}
	}


	int no_of_enemies = enemyposes.size();
	sf::Vector2f heropos;
	heropos.x = newPos.x + 50;
	heropos.y = newPos.y + 75;
	for (int i = 0; i < no_of_enemies; i++) {
		if (newPos.x + 100 > enemyposes[i].x - 50 && newPos.x < enemyposes[i].x + 50 && newPos.y < enemyposes[i].y + 75 && newPos.y + 150 > enemyposes[i].y - 75) {
			sprSheet.setPosition(oldPos);
			newPos = oldPos;
		}

		else if (newPos.x  < enemyposes[i].x + 50 && newPos.x + 100 > enemyposes[i].x - 50 && newPos.y < enemyposes[i].y + 50 && newPos.y + 150 > enemyposes[i].y - 75) {
			sprSheet.setPosition(oldPos);
			newPos = oldPos;
		}

		else if (newPos.y + 150 > enemyposes[i].y - 75 && newPos.y < enemyposes[i].y + 50 && newPos.x < enemyposes[i].x + 50 && newPos.x + 100 > enemyposes[i].x - 50) {
			sprSheet.setPosition(oldPos);
			newPos = oldPos;
		}

		else if (newPos.y  < enemyposes[i].y + 50 && newPos.y + 150 > enemyposes[i].y - 75 && newPos.x < enemyposes[i].x + 50 && newPos.x + 100 > enemyposes[i].x - 50) {
			sprSheet.setPosition(oldPos);
			newPos = oldPos;
		}
	}





	HPpercent = 100 * (float)(hp / MAX_HEALTH[level - 1]);
	XPpercent = 100 * (float)(xp / XP_TARGET[level - 1]);


	checkLevelUp();
}


void Hero::consumePotion()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		if (canConsumePotion)
		{
			if (potions == 0 || hp == MAX_HEALTH[level - 1])
				return;
			else
			{
				potions--;
				if (hp + 60 > MAX_HEALTH[level - 1])
					hp = MAX_HEALTH[level - 1];
				else
					hp = hp + 60;
				canConsumePotion = false;
			}
			
		}
	}
	
}

int Hero::getPotionCount()
{
	return potions;
}

sf::Vector2f Hero::getPosition()
{
	sf::Vector2f position;
	position.x = (left + right) / 2;
	position.y = (top + bottom) / 2;
	return position;
}


void Hero::setName(std::string input)
{
	name.assign(input);
}

std::string Hero::getName()
{
	return name;
}

int Hero::getLevel()
{
	return level;
}

float Hero::getHPpercent()
{
	return HPpercent;
}
float Hero::getXPpercent()
{
	return XPpercent;
}


bool Hero::hit(sf::Vector2f enemypos) {
	sf::Vector2f  heropos = getPosition();
	sf::CircleShape heroCirc;
	heroCirc.setPosition(heropos);
	heroCirc.setRadius(120);
		sf::CircleShape enemyCirc;
		enemyCirc.setPosition(enemypos);
		enemyCirc.setRadius(120);

		if (sqrt(pow(heroCirc.getPosition().x - enemyCirc.getPosition().x, 2) +
			pow(heroCirc.getPosition().y - enemyCirc.getPosition().y, 2)) >=
			heroCirc.getRadius() + enemyCirc.getRadius()) {
			return false;
		}
		else {
			if (heroCirc.getPosition().x < enemyCirc.getPosition().x  && heroCirc.getPosition().y <= enemyCirc.getPosition().y) {
				if (source.y == RIGHT || source.y == DOWN) {
					return true;
				}
				else {
					return false;
				}
			}
			else if (heroCirc.getPosition().x < enemyCirc.getPosition().x  && heroCirc.getPosition().y >= enemyCirc.getPosition().y) {
				if (source.y == RIGHT || source.y == UP) {
					return true;
				}
				else {
					return false;
				}
			}




			if (heroCirc.getPosition().x > enemyCirc.getPosition().x  && heroCirc.getPosition().y <= enemyCirc.getPosition().y) {
				if (source.y == LEFT || source.y == DOWN) {
					return true;
				}
				else {
					return false;
				}
			}
			else if (heroCirc.getPosition().x > enemyCirc.getPosition().x  && heroCirc.getPosition().y >= enemyCirc.getPosition().y) {
				if (source.y == LEFT || source.y == UP) {
					return true;
				}
				else {
					return false;
				}
			}



			if (heroCirc.getPosition().y < enemyCirc.getPosition().y  && heroCirc.getPosition().x <= enemyCirc.getPosition().x) {
				if (source.y == RIGHT || source.y == DOWN) {
					return true;
				}
				else {
					return false;
				}
			}
			else if (heroCirc.getPosition().y < enemyCirc.getPosition().y  && heroCirc.getPosition().x >= enemyCirc.getPosition().x) {
				if (source.y == LEFT || source.y == DOWN) {
					return true;
				}
				else {
					return false;
				}
			}



			if (heroCirc.getPosition().y > enemyCirc.getPosition().y  && heroCirc.getPosition().x <= enemyCirc.getPosition().x) {
				if (source.y == RIGHT || source.y == UP) {
					return true;
				}
				else {
					return false;
				}
			}
			else if (heroCirc.getPosition().y > enemyCirc.getPosition().y  && heroCirc.getPosition().x >= enemyCirc.getPosition().x) {
				if (source.y == LEFT || source.y == UP) {
					return true;
				}
				else {
					return false;
				}

			}
		
	}

}

void Hero::getHit() {
	hp -= 3;
}


void Hero::enemydefeat() {
	xp = xp + 60;
}

void Hero::potionPickup() {
	potions++;
}

void Hero::getHit_boss() {
	hp -= 1;
}

float Hero::getHP() {
	return hp;
}

bool Hero::hit_boss(sf::Vector2f bosspos) {
	sf::Vector2f  heropos = getPosition();
	sf::CircleShape heroCirc;
	heroCirc.setPosition(heropos);
	heroCirc.setRadius(120);
	sf::CircleShape enemyCirc;
	enemyCirc.setPosition(bosspos);
	enemyCirc.setRadius(120);

	if (sqrt(pow(heroCirc.getPosition().x - enemyCirc.getPosition().x, 2) +
		pow(heroCirc.getPosition().y - enemyCirc.getPosition().y, 2)) >=
		heroCirc.getRadius() + enemyCirc.getRadius()) {
		return false;
	}
	else {
		return true;
		
	}
}
