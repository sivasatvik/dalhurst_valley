#include "Dragon.h"
#include "common.h"



Dragon::Dragon(sf::Vector2f position)
{
	texSheet.loadFromFile("assets/images/dragon.png");
	sprSheet.setTexture(texSheet);
	sprSheet.setPosition(position);
	rectIn.setPosition(sf::Vector2f(position.x + 2, position.y + 2));
	rectOut.setPosition(position);
	source.x = 0;
	source.y = DOWN;
	speed = 5;
	health = 1500;
	newpos = position;
	rectIn.setSize(sf::Vector2f(296, 8));
	rectIn.setFillColor(sf::Color::Red);
	rectOut.setSize(sf::Vector2f(300, 10));
	rectOut.setFillColor(sf::Color::Black);
	i = 0;
	fireball1 = new FireBall();
	fireball2 = new FireBall();
	shoot1 = shoot2 = 0;
}


Dragon::~Dragon()
{
}




void Dragon::orient(int direction) {
	source.y = direction;
	sf::Time time = flyClock.getElapsedTime();
	if (time.asSeconds() > 0.15) {
		source.x = (source.x + 1) % 4;
		flyClock.restart().asSeconds();
	}
}

void Dragon::drawDragon() {
	sprSheet.setTextureRect(sf::IntRect(source.x * 300, source.y * 300, 300, 300));
	window.draw(rectOut);
	window.draw(rectIn);
	window.draw(sprSheet);
	if (shoot1)
		fireball1->drawFireball();
	if (shoot2)
		fireball2->drawFireball();
}

void Dragon::Update() {
	sf::Time time = walkClock.getElapsedTime();
	sf::Thread fireball_1(&FireBall::Update, fireball1);
	sf::Thread fireball_2(&FireBall::Update, fireball2);

	if (i >= 0 && i<180) {
		orient(DOWN);
		i++;

	}
	if (i >= 180 && i<320) {
		moveRight();
		i++;
	}
	if (i >= 320 && i<500) {
		orient(DOWN);
		i++;
	}
	if (i >= 500 && i<780) {
		moveLeft();
		i++;
	}
	if (i >= 780 && i<960) {
		orient(DOWN);
		i++;
	}
	if (i >= 960 && i < 1240) {
		moveRight();
		i++;
	}
	if (i >= 1240) {
		i = 320;
	}
	sprSheet.setPosition(newpos);
	sf::Time time1 = fireBall.getElapsedTime();
	if (i == 120) {
		fireball1->setPosition(getPosition_OD());
		shoot1 = 1;
	}
	if (i == 250) {
		delete fireball1;
		fireball1 = new FireBall();
		fireball1->setPosition(getPosition_OR());
		shoot1 = 1;
	}
	if (i == 400) {
		delete fireball1;
		fireball1 = new FireBall();
		fireball1->setPosition(getPosition_OD());
		shoot1 = 1;
	}
	if (i == 420) {
		delete fireball2;
		fireball2 = new FireBall();
		fireball2->setPosition(getPosition_OD());
		shoot2 = 1;
	}
	if (i == 600 || i == 700) {
		delete fireball1;
		fireball1 = new FireBall();
		fireball1->setPosition(getPosition_OL());
		shoot1 = 1;
	}
	if (i == 650) {
		delete fireball2;
		fireball2 = new FireBall();
		fireball2->setPosition(getPosition_OD());
		shoot2 = 1;
	}
	if (i == 880) {
		delete fireball1;
		fireball1 = new FireBall();
		fireball1->setPosition(getPosition_OD());
		shoot1 = 1;
	}
	if (i == 900) {
		delete fireball2;
		fireball2 = new FireBall();
		fireball2->setPosition(getPosition_OD());
		shoot2 = 1;
	}
	if (i == 1050 || i == 1150) {
		delete fireball1;
		fireball1 = new FireBall();
		fireball1->setPosition(getPosition_OR());
		shoot1 = 1;
	}
	if (shoot1) {
		fireball_1.launch();
		if (fireball1->exhausted) {
			shoot1 = 0;
		}
	}
	if (shoot2) {
		fireball_2.launch();
		if (fireball2->exhausted) {
			shoot2 = 0;
		}
	}
}


void Dragon::moveRight() {
	orient(RIGHT);
	newpos.x += speed;
	rectIn.setPosition(newpos);
	rectOut.setPosition(newpos);
}


void Dragon::moveLeft() {
	orient(LEFT);
	newpos.x -= speed;
	rectIn.setPosition(newpos);
	rectOut.setPosition(newpos);
}

sf::Vector2f Dragon::getPosition_OD() {
	sf::Vector2f position;
	position.x = sprSheet.getPosition().x + 150;
	position.y = sprSheet.getPosition().y + 270;
	return position;
}

sf::Vector2f Dragon::getPosition_OR() {
	sf::Vector2f position;
	position.x = sprSheet.getPosition().x + 270;
	position.y = sprSheet.getPosition().y + 150;
	return position;
}


sf::Vector2f Dragon::getPosition_OL() {
	sf::Vector2f position;
	position.x = sprSheet.getPosition().x + 30;
	position.y = sprSheet.getPosition().y + 150;
	return position;
}


sf::Vector2f Dragon::getPosition() {
	sf::Vector2f position;
	position.x = sprSheet.getPosition().x + 150;
	position.y = sprSheet.getPosition().y + 150;
	return position;
}

void Dragon::getHit() {
	sf::Vector2f boss_health = rectIn.getSize();
	boss_health.x -= hero->getDamage()/5;
	health -= hero->getDamage();
	if (boss_health.x <= 0) {
		rectIn.setSize(sf::Vector2f(0, 0));
	}
	else {
		rectIn.setSize(boss_health);
	}
}



int Dragon::getHealth() {
	return health;
}