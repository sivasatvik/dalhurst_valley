#include <SFML/Graphics.hpp>
#include "StaticViewer.h"
#include "common.h"



StaticViewer::StaticViewer(sf::Vector2f center, sf::Vector2f size)
{
	view.setCenter(center);
	view.setSize(size);
}

void StaticViewer::setView()
{
	window.setView(view);
}

StaticViewer::~StaticViewer()
{
}
