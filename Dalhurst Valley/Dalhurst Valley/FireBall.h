#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"

class FireBall
{
	sf::Texture texSheet;
	sf::Sprite sprSheet;
	sf::Vector2f heropos;
	sf::Vector2f newpos;
	int speed;

public:
	bool exhausted;
	FireBall(/*sf::Vector2f position*/);
	~FireBall();
	void Update();
	void setPosition(sf::Vector2f position);
	void drawFireball();
	sf::Vector2f getPosition();
	void shoot();
};