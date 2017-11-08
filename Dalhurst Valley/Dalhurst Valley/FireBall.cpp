#include "FireBall.h"
#include "common.h"



FireBall::FireBall()
{
	texSheet.loadFromFile("assets/images/fireball.png");
	sprSheet.setTexture(texSheet);

	heropos = hero->getPosition();

	speed = 10;
	exhausted = 0;
}


FireBall::~FireBall()
{
}

void FireBall::setPosition(sf::Vector2f position) {
	newpos = position;
	sprSheet.setPosition(position);
}



void FireBall::drawFireball() {
	sprSheet.setTextureRect(sf::IntRect(0, 0, 75, 75));
	window.draw(sprSheet);
}


void FireBall::Update() {
	sf::Vector2f updated_heropos = hero->getPosition();
	sf::Vector2f oldpos = getPosition();
	if (oldpos.x < heropos.x) {
		newpos.x += speed;
	}
	if (oldpos.y < heropos.y) {
		newpos.y += speed;
	}
	if (oldpos.x > heropos.x) {
		newpos.x -= speed;
	}
	if (oldpos.y > heropos.y) {
		newpos.y -= speed;
	}
	if (((oldpos.x - heropos.x <10) && (oldpos.x - heropos.x>-10)) && ((oldpos.y - heropos.y<10) && (oldpos.y - heropos.y>-10))) {
		exhausted = 1;
	}
	else {
		sf::Vector2f updated_heropos = hero->getPosition();
		sf::CircleShape heroCirc;
		heroCirc.setPosition(updated_heropos);
		heroCirc.setRadius(50);
		sf::CircleShape flameCirc;
		flameCirc.setPosition(getPosition());
		flameCirc.setRadius(50);
		if (sqrt(pow(heroCirc.getPosition().x - flameCirc.getPosition().x, 2) +
			pow(heroCirc.getPosition().y - flameCirc.getPosition().y, 2)) <=
			heroCirc.getRadius() + flameCirc.getRadius()) {
			hero->getHit_boss();
		}
	}
	sprSheet.setPosition(newpos);
}

sf::Vector2f FireBall::getPosition() {
	sf::Vector2f position;
	position.x = sprSheet.getPosition().x;
	position.y = sprSheet.getPosition().y;
	return position;
}


void FireBall::shoot() {
	Update();
	drawFireball();
}