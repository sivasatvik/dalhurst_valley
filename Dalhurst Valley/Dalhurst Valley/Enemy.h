#include <SFML/Graphics.hpp>
#include "MapGenerator.h"
#include "Hero.h"
#pragma once
class Enemy
{
private:
	enum direction { LEFT, RIGHT, UP, DOWN };
	int health;
	sf::Texture texSheet, texPotion;
	sf::Sprite sprSheet, sprPotion;
	sf::Vector2i source;
	sf::Clock walkClock;
	float speed;
	float bottom, left, right, top;
	sf::Vector2i tL, tR, bL, bR;
	std::vector<sf::Vector2i>tiles;
	sf::RectangleShape rectIn, rectOut;
	bool animateAttack;
	int i, j;
	bool pauseAttack;
	
public:
	MapGenerator *map;
	Enemy(sf::Vector2f position);
	~Enemy();
	void Update();
	void orient(int direction);
	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
	void drawEnemy();
	void getHit();
	int getHealth();
	sf::Vector2f getPosition();
	void cycleAttack();

};





