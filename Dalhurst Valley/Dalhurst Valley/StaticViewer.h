#pragma once
class StaticViewer
{
private:
	sf::View view;
public:
	StaticViewer(sf::Vector2f center, sf::Vector2f size);
	~StaticViewer();
	void setView();
};

