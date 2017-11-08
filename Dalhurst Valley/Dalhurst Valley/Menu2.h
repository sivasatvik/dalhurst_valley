#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define MAX_NUM_OF_ITEMS 2

class Menu2
{
public:
	Menu2(float x, float y, float height, char *menu1, char *menu2);
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int getPressedItem();
private:
	int selectedItemIndex;
	sf::Texture texSelect;
	sf::Sprite sprSelect;
	sf::SoundBuffer soundBufferSwing;
	sf::SoundBuffer soundBufferHit;
	sf::Sound soundSwing;
	sf::Sound soundHit;
	sf::Font fontSelected, font;
	sf::Text txtList[MAX_NUM_OF_ITEMS];
};

