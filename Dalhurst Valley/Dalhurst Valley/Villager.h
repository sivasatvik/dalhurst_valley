#pragma once
#include <SFML/Graphics.hpp>

class Villager
{
private:
	enum direction {DOWN, LEFT, RIGHT, UP};
	sf::Texture texSheet;
	sf::Sprite sprSheet;
	sf::Vector2i source;
	sf::Vector2f newPos;
	sf::Clock walkClock;
	float speed;
	int i;
	sf::Time wait_time;
	int dir;
public:
	Villager(sf::Vector2f spawnPoint, int direction, int skin);
	void orient(int direction);
	void drawVillager();
	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
	void walkAround();
	float bottom, left, right, top;
	sf::Vector2f getPosition();
	~Villager();
};

