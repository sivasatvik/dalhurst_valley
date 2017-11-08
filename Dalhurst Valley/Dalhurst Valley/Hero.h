#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MapGenerator.h"
#include <string>




class Hero
{
private:
	enum direction {LEFT, RIGHT, UP, DOWN};
	float MAX_HEALTH[5] = { 100, 180, 250, 400, 600 };
	float XP_TARGET[4] = { 100, 250, 500, 800 };
	float DAMAGE[5] = { 25, 50, 75, 100, 125 };

	int level, potions;
	float hp, xp, damage;
	float HPpercent, XPpercent;
	sf::Texture texSheet;
	sf::Sprite sprSheet;
	sf::Vector2i source;
	sf::Vector2f newPos;
	sf::Clock walkClock;
	sf::Clock attackClock;
	float speed;
	std::string name;
	sf::CircleShape hitcircle;
	bool animateAttack;
	bool canConsumePotion;
	int i, j;




public:
	Hero();
	~Hero();
	void setSpawnPoint(sf::Vector2f postion);
	void orient(int direction);
	void update(MapGenerator *map, std::vector<sf::Vector2f> enemyposes);
	void drawHero();
	float bottom, left, right, top;
	sf::Vector2f getPosition();
	std::vector<sf::Vector2i> tilesTouching;
	void setName(std::string input);
	std::string getName();
	int getLevel();
	void cycleAttack();
	void setAttack();
	void resetOrientation();
	float getHPpercent();
	float getXPpercent();
	bool hit(sf::Vector2f);
	void getHit();
	void enemydefeat();
	void potionPickup();
	void getHit_boss();
	bool hit_boss(sf::Vector2f);
	void checkLevelUp();
	void levelUp();
	void consumePotion();
	int getPotionCount();
	void checkIfDead();
	float getHP();
	float getDamage();
};