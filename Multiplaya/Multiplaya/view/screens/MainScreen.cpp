#include "MainScreen.h"

#include <iostream>
#include <string>
#include <sstream>

namespace mp
{
	MainScreen::MainScreen(const sf::Vector2u &resolution)
	{
		initBackground(resolution);
		initFont();
		initButtons();
		initText();
	}

	void MainScreen::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(*backgroundSprite);
		window.draw(*gameTitleText);
		Screen::draw(window, states);
	}

	void MainScreen::initFont()
	{
		font = new sf::Font();
		font->loadFromFile("resources/gothic.ttf");
	}

	void MainScreen::initBackground(const sf::Vector2u &resolution)
	{
		backgroundTexture = new sf::Texture();
		
		// Pick one of three background images
		backgroundTexture = getRandomBackground(3);
		backgroundSprite = new sf::Sprite();
		backgroundSprite->setTexture(*backgroundTexture);
		backgroundSprite->setPosition(0, 0);
		
		// calculate scaling to fit resolution
		backgroundSprite->scale( (float) resolution.x / backgroundTexture->getSize().x,  (float) resolution.y / backgroundTexture->getSize().y);
	}

	void MainScreen::initButtons()
	{
		Button* joinButton = new Button(0, 440, 250, 50, "Join game");
		joinButton->setFont(*font);
		joinButton->setTextPosition(60, 5);
		joinButton->setTextColor(sf::Color::Black);
		setGUIElement("joinButton",joinButton);

		Button* hostButton = new Button(0, 500, 250, 50, "Host game");
		hostButton->setFont(*font);
		hostButton->setTextPosition(60, 5);
		hostButton->setTextColor(sf::Color::Black);
		setGUIElement("hostButton", hostButton);

		Button* settingsButton = new Button(0, 560, 250, 50, "Settings");
		settingsButton->setFont(*font);
		settingsButton->setTextPosition(60, 5);
		settingsButton->setTextColor(sf::Color::Black);
		setGUIElement("settingsButton", settingsButton);

		Button* exitButton = new Button(0, 620, 250, 50, "Exit game");
		exitButton->setFont(*font);
		exitButton->setTextPosition(60, 5);
		exitButton->setTextColor(sf::Color::Black);
		setGUIElement("exitButton", exitButton);
	}

	void MainScreen::initText()
	{
		gameTitleText = new sf::Text("Multiplaya");
		gameTitleText->setFont(*font);
		gameTitleText->setStyle(sf::Text::Bold);
		gameTitleText->setColor(sf::Color::White);
		gameTitleText->setPosition(20, 20);
		gameTitleText->setCharacterSize(40);
	}

	sf::Texture* MainScreen::getRandomBackground(int nrOfBackgrounds)
	{
		srand ( time(NULL) );
		int randomInt = rand() % nrOfBackgrounds;

		switch(randomInt) {
			case 0:
				return ResourceHandler::instance().getTexture("resources/ui/backgrounds/bg_title0.jpg");
			case 1:
				return ResourceHandler::instance().getTexture("resources/ui/backgrounds/bg_title1.jpg");
			case 2:
				return ResourceHandler::instance().getTexture("resources/ui/backgrounds/bg_title2.jpg");
		}
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
}