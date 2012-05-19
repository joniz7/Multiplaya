#include "JoinGameController.h"

namespace mp
{
	JoinGameController::JoinGameController(sf::RenderWindow* window, Screen* joinGameScreen) : IController(window, joinGameScreen)
	{
		cancelButton = joinGameScreen->getElement("cancelButton");
		connectButton = joinGameScreen->getElement("connectButton");
		ipTextField = joinGameScreen->getElement("ipTextField");
		portTextField = joinGameScreen->getElement("portTextField");

		ipTextClicked = false;
		portTextClicked = false;

	}

	JoinGameController::~JoinGameController()
	{
		//dtor
	}

	void JoinGameController::handleInput()
	{
		// for hover effects
		while (getRenderWindow()->pollEvent(ev))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getRenderWindow());
			getScreen()->hover(mousePos);

			if (ev.type == sf::Event::MouseButtonReleased)
			{
				
				if( connectButton->isMouseOver(mousePos) )
				{
					connectButton->click();
					networkHandler->connectToServer("Jonte");
					networkHandler->setIPAddress(ipTextField->getText());
					networkHandler->setAsClient();
					GameState::getInstance()->setGameState(GameState::HOST_GAME);
				}
				
				if ( cancelButton->isMouseOver(mousePos) )
				{
					cancelButton->click();
					GameState::getInstance()->setGameState(GameState::MAIN_SCREEN);
				}

				if ( ipTextField->isMouseOver(mousePos) )
				{
					// lose focus
					if (portTextClicked)
					{
						portTextField->click();
						portTextClicked = false;
					}

					if (ipTextClicked)
					{
						ipTextField->click();
						ipTextClicked = false;
					}
					else
					{
						ipTextField->click();
						ipTextClicked = true;
					}
				}

				if ( portTextField->isMouseOver(mousePos) )
				{
					// if ipTextField is clicked then lose focus..
					if (ipTextClicked)
					{
						ipTextField->click();
						ipTextClicked = false;
					}

					if (portTextClicked)
					{
						portTextField->click();
						portTextClicked = false;
					}
					else
					{
						portTextField->click();
						portTextClicked = true;
					}
				}
			}

			if (ev.type == sf::Event::TextEntered)
			{
				if (isNumber(ev))
				{
					if (ipTextClicked)
						ipTextField->setText(ipTextField->getText() + ev.text.unicode);
					if (portTextClicked)
						portTextField->setText(portTextField->getText() + ev.text.unicode);
				}
				else if (isDot(ev))
				{
					// "remove" the possibility to input double dots
					if (ipTextClicked)
						ipTextField->setText(ipTextField->getText() + ev.text.unicode);

					if (portTextClicked)
						portTextField->setText(portTextField->getText() + ev.text.unicode);
				}
				else if (isBackspace(ev))
				{
					if (ipTextClicked)
					{
						removeLastCharacter(ipTextField);
					}
						
					if (portTextClicked)
					{
						removeLastCharacter(portTextField);
					}	
				}
			} // end of textentered
		} // end of pollEvent loop
	}

	void JoinGameController::removeLastCharacter(GUIElement* element)
	{
		int textLength = element->getText().getSize();
		if (textLength > 0)
		{
			std::string text = element->getText();
			element->setText(text.erase(textLength - 1, 1));
		}
	}

	bool JoinGameController::isNumber(sf::Event &ev)
	{
		return (ev.text.unicode >= 48 && ev.text.unicode <= 57 );
	}

	bool JoinGameController::isDot(sf::Event &ev)
	{
		return ev.text.unicode == 46;
	}

	bool JoinGameController::isBackspace(sf::Event &ev)
	{
		return ev.text.unicode == 8;
	}
	
}