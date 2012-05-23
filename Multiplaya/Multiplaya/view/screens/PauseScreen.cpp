#include "PauseScreen.h"

#include <iostream>
#include <string>
#include <sstream>

namespace mp
{
	PauseScreen::PauseScreen(const sf::Vector2u &resolution)
	{
		initBackground(resolution);
		initFont();
		initButtons();
		initText();
	}

	void PauseScreen::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(*backgroundSprite);
		window.draw(*gameTitleText);
		window.draw(*gameSubtitleText);
		Screen::draw(window, states);
	}

	void PauseScreen::initFont()
	{
		font = new sf::Font();
		font->loadFromFile("resources/gothic.ttf");
	}

	void PauseScreen::initBackground(const sf::Vector2u &resolution)
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

	void PauseScreen::initButtons()
	{

		Button* resumeButton = new Button(0, 500, 300, 50, "Resume game");
		resumeButton->setFont(*font);
		resumeButton->setTextPosition(60, 5);
		resumeButton->setTextColor(sf::Color::Black);
		setGUIElement("resumeButton", resumeButton);

		Button* disconnectButton = new Button(0, 560, 300, 50, "Disconnect");
		disconnectButton->setBackgroundColor(sf::Color(184, 184, 184, 30));
		disconnectButton->setFont(*font);
		disconnectButton->setTextPosition(60, 5);
		disconnectButton->setTextColor(sf::Color::White);
		disconnectButton->enableHovering(false);
		setGUIElement("disconnectButton", disconnectButton);

		Button* exitButton = new Button(0, 620, 300, 50, "Exit game");
		exitButton->setFont(*font);
		exitButton->setTextPosition(60, 5);
		exitButton->setTextColor(sf::Color::Black);
		setGUIElement("exitButton", exitButton);
	}

	void PauseScreen::initText()
	{
		gameTitleText = new sf::Text("Multiplaya");
		gameTitleText->setFont(*font);
		gameTitleText->setStyle(sf::Text::Bold);
		gameTitleText->setColor(sf::Color::White);
		gameTitleText->setPosition(20, 20);
		gameTitleText->setCharacterSize(40);

		gameSubtitleText = new sf::Text("Paused");
		gameSubtitleText->setFont(*font);
		gameSubtitleText->setStyle(sf::Text::Bold);
		gameSubtitleText->setColor(sf::Color::White);
		gameSubtitleText->setPosition(25, 65);
		gameSubtitleText->setCharacterSize(20);
	}

	sf::Texture* PauseScreen::getRandomBackground(int nrOfBackgrounds)
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

	PauseScreen::~PauseScreen()
	{
		delete gameTitleText;
		delete gameSubtitleText;
	}
}