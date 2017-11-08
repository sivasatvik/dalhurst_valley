#include "HUD.h"
#include "common.h"
#include <stdlib.h>
#include <string>

HUD::HUD()
{
	texHealth.loadFromFile("assets/images/HUD/health.png");
	sprHealth.setTexture(texHealth);
	texXP.loadFromFile("assets/images/HUD/xp.png");
	sprXP.setTexture(texXP);
	texRight.loadFromFile("assets/images/HUD/right.png");
	sprRight.setTexture(texRight);
	texLeft.loadFromFile("assets/images/HUD/left.png");
	sprLeft.setTexture(texLeft);
	texIcon.loadFromFile("assets/images/HUD/icon.png");
	sprIcon.setTexture(texIcon);

	fontBoldItalic.loadFromFile("assets/fonts/Sansation_Bold_Italic.ttf");
	fontBold.loadFromFile("assets/fonts/Sansation_Bold.ttf");

	name.setFont(fontBoldItalic);
	level.setFont(fontBoldItalic);
	potion_count.setFont(fontBold);
	name.setCharacterSize(60);
	level.setCharacterSize(30);
	potion_count.setCharacterSize(30);

	negHP = 0;
	negXP = 764;

}

void HUD::updateHUD()
{
	level.setString("LEVEL " + std::to_string(hero->getLevel()) + " - HP: " + std::to_string(hero->getHPpercent()) + " - XP: " + std::to_string(hero->getXPpercent()));
	negHP = (100.0 - hero->getHPpercent()) * 718 / 100;
	negXP = 764 - ((hero->getXPpercent()) * 764 / 100);
	potion_count.setString("POTIONS x " + std::to_string(hero->getPotionCount()));
}


void HUD::setName()
{
	name.setString(hero->getName());
}

void HUD::drawHUD()
{
	sprLeft.setPosition(sf::Vector2f(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).x, sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).y + 900));
	name.setPosition(sf::Vector2f(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).x + 190, sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).y + 895));
	level.setPosition(sf::Vector2f(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).x + 190 + name.getLocalBounds().width + 20, sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).y + 925));
	sprHealth.setPosition(sf::Vector2f(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).x - negHP, sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).y + 900));
	sprXP.setPosition(sf::Vector2f(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).x - negXP, sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).y + 900));
	sprRight.setPosition(sf::Vector2f(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).x + 1020, sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).y + 900));
	sprIcon.setPosition(sf::Vector2f(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).x, sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).y + 830));
	potion_count.setPosition(sf::Vector2f(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).x + 1920 - 30 - potion_count.getLocalBounds().width, sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0, 0))).y + 960));
	window.draw(sprLeft);
	window.draw(sprHealth);
	window.draw(sprXP);
	window.draw(sprIcon);
	window.draw(name);
	window.draw(level);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		window.draw(sprRight);
		window.draw(potion_count);
	}

}

HUD::~HUD()
{
}
