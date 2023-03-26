#include "mainMenu.hpp"

MainMenu::MainMenu(Vector2f position, RenderWindow& window)
{
	this->mainMenuTexture.loadFromFile("./Assets/Void.png");
	this->mainMenuSprite.setTexture(mainMenuTexture);
	this->mainMenuSprite.setScale(Vector2f(16, 9));
	this->mainMenuSprite.setPosition(position);

	this->menuANDTexture.loadFromFile("./Assets/MenuAND.png");
	this->menuORTexture.loadFromFile("./Assets/MenuOR.png");
	this->menuXORTexture.loadFromFile("./Assets/MenuXOR.png");
	
	this->playTexture.loadFromFile("./Assets/StartButton.png");
	this->quitTexture.loadFromFile("./Assets/QuitButton.png");

	this->playSprite.setTexture(this->playTexture);
	this->quitSprite.setTexture(this->quitTexture);

	this->playSprite.setPosition(Vector2f(520, 304));
	this->quitSprite.setPosition(Vector2f(520, 463));

	this->menuANDSprite.setTexture(this->menuANDTexture);
	this->menuANDSprite.setPosition(Vector2f(574, 62));
	
	this->menuORSprite.setTexture(this->menuORTexture);
	this->menuORSprite.setPosition(Vector2f(508, 63));
	
	this->menuXORSprite.setTexture(this->menuXORTexture);
	this->menuXORSprite.setPosition(Vector2f(717, 62));

	update(window);
}

void MainMenu::update(RenderWindow& window)
{
	while (window.isOpen()) {
		while (window.pollEvent(this->ev)) {
			if (this->ev.type == Event::Closed()) {
				window.close();
			}
			else if (this->ev.type == Event::MouseButtonPressed) {
				if (mouseHandler(window) == 1) {
					return;
				}
			}
		}
		drawMainMenu(window);
	}
}

void MainMenu::drawMainMenu(RenderWindow& window)
{
	window.clear();
	window.draw(this->mainMenuSprite);
	window.draw(this->menuANDSprite);
	window.draw(this->menuORSprite);
	window.draw(this->menuXORSprite);
	window.draw(this->playSprite);
	window.draw(this->quitSprite);
	window.display();
}

int MainMenu::mouseHandler(RenderWindow& window) {
	float mouseX = this->ev.mouseButton.x;
	float mouseY = this->ev.mouseButton.y;
	int button = this->ev.mouseButton.button;

	if (mouseX <= 760 && mouseX >= 520) {
		if (mouseY >= 304 && mouseY <= 374) {
			return 1;
		}
		else if (mouseY >= 463 && mouseY <= 533) {
			window.close();
		}
	}
	return 0;
}