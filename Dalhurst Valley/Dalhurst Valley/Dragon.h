#pragma once
#include "Hero.h"
#include <SFML/Graphics.hpp>
#include "FireBall.h"

class Dragon
{
	enum direction { DOWN, LEFT, RIGHT, UP };
	int health;
	sf::Texture texSheet;
	sf::Sprite sprSheet;
	sf::Vector2i source;
	sf::Clock walkClock;
	sf::Clock flyClock;
	sf::Clock fireBall;
	float speed;
	sf::CircleShape hitcircle;
	sf::Vector2f newpos, oldpos;
	int i;
	bool shoot1, shoot2;
	sf::RectangleShape rectIn, rectOut;
	FireBall *fireball1, *fireball2;
public:
	Dragon(sf::Vector2f position);
	~Dragon();
	void orient(int direction);
	void drawDragon();
	void Update();
	void moveRight();
	void moveLeft();
	sf::Vector2f getPosition_OD();
	sf::Vector2f getPosition_OR();
	sf::Vector2f getPosition_OL();
	sf::Vector2f getPosition();
	void getHit();
	int getHealth();
};