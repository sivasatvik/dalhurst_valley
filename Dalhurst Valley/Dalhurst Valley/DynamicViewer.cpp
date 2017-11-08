#include <SFML/Graphics.hpp>
#include "DynamicViewer.h"
#include "common.h"


DynamicViewer::DynamicViewer()
{

}

void DynamicViewer::initViewer(sf::Vector2f heroSpawnPoint)
{
	view.reset(sf::FloatRect(heroSpawnPoint.x + 50 - 960, heroSpawnPoint.y + 100 - 540, 1920, 1080));
}

void DynamicViewer::updateViewer()
{
	heroPos = hero->getPosition();
	view.setCenter(heroPos);
	window.setView(view);
}

DynamicViewer::~DynamicViewer()
{
}
