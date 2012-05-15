#include "MainScreen.h"

#include <iostream>

namespace mp
{
	MainScreen::MainScreen(const sf::Vector2u &resolution)
	{
		// do I choose a sf::Texture or an sf::Image?
		backgroundTexture = new sf::Texture();
		backgroundTexture->loadFromFile("resources/background.jpg");

		backgroundSprite = new sf::Sprite();
		backgroundSprite->setTexture(*backgroundTexture);
		backgroundSprite->setPosition(0, 0);

		// calculate background sprite scaling
		// move to method later on
		backgroundSprite->scale( 2.0f,  1.2f);
		font = new sf::Font();
		font->loadFromFile("resources/gothic.ttf");


		gameTitleText = new sf::Text("Multiplaya");
		gameTitleText->setFont(*font);
		gameTitleText->setStyle(sf::Text::Bold);
		gameTitleText->setColor(sf::Color::Black);
		gameTitleText->setPosition(500, 20);
		gameTitleText->setCharacterSize(40);

		buttons["joinButton"] = new Button(40, 100, 200, 60, "Join game");
		buttons["joinButton"]->setFont(*font);
		buttons["joinButton"]->setFontColor(sf::Color::Black);

		buttons["hostButton"] = new Button(40, 180, 200, 60, "Host game");
		buttons["hostButton"]->setFont(*font);
		buttons["hostButton"]->setFontColor(sf::Color::Black);

		buttons["settingsButton"] = new Button(40, 260, 200, 60, "Settings");
		buttons["settingsButton"]->setFont(*font);
		buttons["settingsButton"]->setFontColor(sf::Color::Black);

		buttons["exitButton"] = new Button(40, 340, 200, 60, "Exit game");
		buttons["exitButton"]->setFont(*font);
		buttons["exitButton"]->setFontColor(sf::Color::Black);

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
		for( std::map<std::string, Button*>::const_iterator it = buttons.begin(); it != buttons.end(); it++ )
		{
		   window.draw(*it->second);
		}
	}

	/*int MainScreen::click(const sf::Vector2i& mousePos)
	{
		if ( buttons["joinButton"]->isMouseOver( mousePos ) )
		{
			std::cout << "Join game" << std::endl;

			return 1;
		}
		else if ( buttons["hostButton"]->isMouseOver( mousePos ) )
		{
			std::cout << "host game" << std::endl;
		}
		else if ( buttons["settingsButton"]->isMouseOver( mousePos ) )
		{
			std::cout << "settings" << std::endl;
		}
		else if ( buttons["exitButton"]->isMouseOver( mousePos ) )
		{
			std::cout << "exit game" << std::endl;
		}

		return 0;
	}*/

	bool MainScreen::hover(const sf::Vector2i& mousePos)
	{
		// put in a function
		buttons["joinButton"]->isMouseOver( mousePos );
		buttons["hostButton"]->isMouseOver( mousePos );
		buttons["settingsButton"]->isMouseOver( mousePos );
		buttons["exitButton"]->isMouseOver( mousePos );

		return true;
	}

	GUIElement* MainScreen::getElement(std::string element)
	{
		return buttons[element];
	}

}