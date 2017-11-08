#include <SFML/Graphics.hpp>
#pragma once

class HUD
{
private:
	sf::Texture texRight, texLeft, texIcon, texHealth, texXP;
	sf::Sprite sprRight, sprLeft, sprIcon, sprHealth, sprXP;
	sf::Font fontBoldItalic, fontBold;
	sf::Text name, level, potion_count;
	float negHP, negXP;
public:
	HUD();
	void updateHUD();
	void setName();
	void drawHUD();
	~HUD();
};

