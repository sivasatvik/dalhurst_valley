#pragma once
#include <SFML/Graphics.hpp>
class DynamicViewer
{
private:
	sf::View view;
	sf::Vector2f heroPos;
public:
	DynamicViewer();
	~DynamicViewer();
	void initViewer(sf::Vector2f heroSpawnPoint);
	void updateViewer();
};

