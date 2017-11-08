#include "State_Pause.h"
#include "common.h"


State_Pause::State_Pause()
{
	menu = new Menu3(880, 540, 400, "RESUME", "CONTROLS", "EXIT");
	viewer = new StaticViewer(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080));
}



State_Pause::~State_Pause()
{
}

void State_Pause::init_state()
{
	if (initState)
	{
		viewer->setView();
		initState = false;
	}

}

void State_Pause::handle_events()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Up:
				menu->MoveUp();
				break;
			case sf::Keyboard::Down:
				menu->MoveDown();
				break;
			case sf::Keyboard::Return:
				switch (menu->getPressedItem()) {
				case 0:
					unpause_game();
					break;
				case 1:
					//;
					break;
				case 2:
					exit_game();
					break;
				}
			}
		}
	}
}

void State_Pause::logic()
{

}

void State_Pause::render()
{
	menu->draw(window);
}

