#include "MainScreen.h"

#include <iostream>
#include <string>
#include <sstream>

namespace mp
{
	MainScreen::MainScreen(const sf::Vector2u &resolution)
	{
		// do I choose a sf::Texture or an sf::Image?
		backgroundTexture = new sf::Texture();
		
		// Pick one of three background images
		srand ( time(NULL) );
		int randomInt = rand() % 3;

		switch(randomInt) {
			case 0:
				backgroundTexture = ResourceHandler::instance().getTexture("resources/ui/backgrounds/bg_title0.jpg");
			break;
			case 1:
				backgroundTexture = ResourceHandler::instance().getTexture("resources/ui/backgrounds/bg_title1.jpg");
			break;
			case 2:
				backgroundTexture = ResourceHandler::instance().getTexture("resources/ui/backgrounds/bg_title2.jpg");
			break;
		}

		backgroundSprite = new sf::Sprite();
		backgroundSprite->setTexture(*backgroundTexture);
		backgroundSprite->setPosition(0, 0);

		// calculate background sprite scaling
		// move to method later on
		backgroundSprite->scale( (float) resolution.x / backgroundTexture->getSize().x,  (float) resolution.y / backgroundTexture->getSize().y);
		font = new sf::Font();
		font->loadFromFile("resources/gothic.ttf");

		gameTitleText = new sf::Text("Multiplaya");
		gameTitleText->setFont(*font);
		gameTitleText->setStyle(sf::Text::Bold);
		gameTitleText->setColor(sf::Color::White);
		gameTitleText->setPosition(20, 20);
		gameTitleText->setCharacterSize(40);

		Button* joinButton = new Button(0, 440, 250, 50, "Join game");
		joinButton->setFont(*font);
		joinButton->setTextPosition(60, 5);
		joinButton->setFontColor(sf::Color::Black);
		setGUIElement("joinButton",joinButton);

		Button* hostButton = new Button(0, 500, 250, 50, "Host game");
		hostButton->setFont(*font);
		hostButton->setTextPosition(60, 5);
		hostButton->setFontColor(sf::Color::Black);
		setGUIElement("hostButton", hostButton);

		Button* settingsButton = new Button(0, 560, 250, 50, "Settings");
		settingsButton->setFont(*font);
		settingsButton->setTextPosition(60, 5);
		settingsButton->setFontColor(sf::Color::Black);
		setGUIElement("settingsButton", settingsButton);

		Button* exitButton = new Button(0, 620, 250, 50, "Exit game");
		exitButton->setFont(*font);
		exitButton->setTextPosition(60, 5);
		exitButton->setFontColor(sf::Color::Black);
		setGUIElement("exitButton", exitButton);

	}

	MainScreen::~MainScreen()
	{
		/*
		delete gameTitleText;
		delete joinGameButton;
		delete hostGameButton;
		delete settingsButton;
		delete exitGameButton;
		delete font;
		*/
	}

	void MainScreen::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(*backgroundSprite);
		window.draw(*gameTitleText);
		Screen::draw(window, states);
	}
}