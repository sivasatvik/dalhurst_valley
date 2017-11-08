#include "Menu3.h"



Menu3::Menu3(float x, float y, float height, char *menu1, char *menu2, char *menu3)
{
	soundBufferSwing.loadFromFile("assets/sounds/sword_swing.wav");
	soundSwing.setBuffer(soundBufferSwing);
	soundBufferHit.loadFromFile("assets/sounds/sword_metal_hit.wav");
	soundHit.setBuffer(soundBufferHit);
	soundSwing.setVolume(3);
	soundHit.setVolume(3);

	texSelect.loadFromFile("assets/images/select.png");
	sprSelect.setTexture(texSelect);
	fontSelected.loadFromFile("assets/fonts/Sansation_Bold_Italic.ttf");
	font.loadFromFile("assets/fonts/Sansation_Bold.ttf");
	txtList[0].setFont(fontSelected);
	txtList[0].setString(menu1);
	txtList[0].setCharacterSize(70);
	txtList[0].setColor(sf::Color::White);
	txtList[0].setPosition(sf::Vector2f(x, y + height / (MAX_NUM_OF_ITEMS + 1) * 1 - 20));
	sprSelect.setPosition(sf::Vector2f(x - 35, y + height / (MAX_NUM_OF_ITEMS + 1) * 1 - 12));

	txtList[1].setFont(font);
	txtList[1].setString(menu2);
	txtList[1].setCharacterSize(40);
	txtList[1].setColor(sf::Color(210, 210, 210));
	txtList[1].setPosition(sf::Vector2f(x, y + height / (MAX_NUM_OF_ITEMS + 1) * 2));

	txtList[2].setFont(font);
	txtList[2].setString(menu3);
	txtList[2].setCharacterSize(40);

	txtList[2].setColor(sf::Color(210, 210, 210));
	txtList[2].setPosition(sf::Vector2f(x, y + height / (MAX_NUM_OF_ITEMS + 1) * 3));
	

	selectedItemIndex = 0;
}


void Menu3::draw(sf::RenderWindow &window) 
{
	window.draw(sprSelect);
	for (int i = 0; i < MAX_NUM_OF_ITEMS; i++) {
		window.draw(txtList[i]);
	}
}


void Menu3::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		soundSwing.play();
		sf::Vector2f tempLocation;
		tempLocation = txtList[selectedItemIndex].getPosition();
		txtList[selectedItemIndex].setPosition(tempLocation.x, tempLocation.y + 20);
		txtList[selectedItemIndex].setColor(sf::Color(210, 210, 210));
		txtList[selectedItemIndex].setFont(font);
		txtList[selectedItemIndex].setCharacterSize(40);
		selectedItemIndex--;
		txtList[selectedItemIndex].setColor(sf::Color::White);
		txtList[selectedItemIndex].setCharacterSize(70);
		txtList[selectedItemIndex].setFont(fontSelected);
		tempLocation = txtList[selectedItemIndex].getPosition();
		txtList[selectedItemIndex].setPosition(tempLocation.x, tempLocation.y - 20);
		sprSelect.setPosition(tempLocation.x - 35, tempLocation.y - 12);


	}
}

void Menu3::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUM_OF_ITEMS) {
		soundSwing.play();
		sf::Vector2f tempLocation;
		tempLocation = txtList[selectedItemIndex].getPosition();
		txtList[selectedItemIndex].setPosition(tempLocation.x, tempLocation.y + 20);
		txtList[selectedItemIndex].setColor(sf::Color(210, 210, 210));
		txtList[selectedItemIndex].setFont(font);
		txtList[selectedItemIndex].setCharacterSize(40);
		selectedItemIndex++;
		txtList[selectedItemIndex].setColor(sf::Color::White);
		txtList[selectedItemIndex].setCharacterSize(70);
		txtList[selectedItemIndex].setFont(fontSelected);
		tempLocation = txtList[selectedItemIndex].getPosition();
		txtList[selectedItemIndex].setPosition(tempLocation.x, tempLocation.y - 20);
		sprSelect.setPosition(tempLocation.x - 35, tempLocation.y - 12);
	}
}

int Menu3::getPressedItem()
{
	soundHit.play();
	return selectedItemIndex;
}