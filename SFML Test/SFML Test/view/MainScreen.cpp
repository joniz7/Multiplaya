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
		std::cout<<"Din mamma: "<<randomInt<<std::endl;
		std::stringstream backgroundFile;
		backgroundFile << "resources/background" << randomInt << ".jpg";
		backgroundTexture->loadFromFile( backgroundFile.str() );

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
		gameTitleText->setColor(sf::Color::Black);
		gameTitleText->setPosition(500, 20);
		gameTitleText->setCharacterSize(40);

		guiElements["joinButton"] = new Button(40, 100, 200, 60, "Join game");
		guiElements["joinButton"]->setFont(*font);
		guiElements["joinButton"]->setFontColor(sf::Color::Black);

		guiElements["hostButton"] = new Button(40, 180, 200, 60, "Host game");
		guiElements["hostButton"]->setFont(*font);
		guiElements["hostButton"]->setFontColor(sf::Color::Black);

		guiElements["settingsButton"] = new Button(40, 260, 200, 60, "Settings");
		guiElements["settingsButton"]->setFont(*font);
		guiElements["settingsButton"]->setFontColor(sf::Color::Black);

		guiElements["exitButton"] = new Button(40, 340, 200, 60, "Exit game");
		guiElements["exitButton"]->setFont(*font);
		guiElements["exitButton"]->setFontColor(sf::Color::Black);

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

		// iterate ovef buttons map instead
		// draw buttons
		for( std::map<std::string, Button*>::const_iterator it = guiElements.begin(); it != guiElements.end(); it++ )
		{
		   window.draw(*it->second);
		}
	}

	bool MainScreen::hover(const sf::Vector2i& mousePos)
	{
		// put in a function
		guiElements["joinButton"]->isMouseOver( mousePos );
		guiElements["hostButton"]->isMouseOver( mousePos );
		guiElements["settingsButton"]->isMouseOver( mousePos );
		guiElements["exitButton"]->isMouseOver( mousePos );

		return true;
	}

	GUIElement* MainScreen::getElement(std::string element)
	{
		return guiElements[element];
	}

}