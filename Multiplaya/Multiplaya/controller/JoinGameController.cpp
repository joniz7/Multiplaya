#include "JoinGameController.h"

namespace mp
{
	JoinGameController::JoinGameController(sf::RenderWindow* window, Screen* joinGameScreen) : IController(window, joinGameScreen)
	{
		cancelButton = joinGameScreen->getGUIElement("cancelButton");
		connectButton = joinGameScreen->getGUIElement("connectButton");
		ipTextField = (TextField*) joinGameScreen->getGUIElement("ipTextField");
		portTextField = (TextField*) joinGameScreen->getGUIElement("portTextField");
	}

	JoinGameController::~JoinGameController()
	{
		//dtor
	}

	void JoinGameController::handleInput()
	{
		float elapsed;
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
					networkHandler->connectToServer("Jonte", "172.16.0.3");
					clock.restart();
					elapsed = clock.getElapsedTime().asSeconds();
					while(!networkHandler->isConnectedToServer() && elapsed<3)
					{
						elapsed = clock.getElapsedTime().asSeconds();
					}

					if(networkHandler->isConnectedToServer())
					{
						//networkHandler->setIPAddress(ipTextField->getText());
						networkHandler->setAsClient();
						// Change screen in main controller.
						notifyObservers(START_GAME, 0);
					}
				}

				if ( cancelButton->isMouseOver(mousePos) )
				{
					cancelButton->click();
					notifyObservers(SHOW_MAIN_MENU, 0);
				}

				if ( ipTextField->isMouseOver(mousePos) )
				{
					// lose focus
					if (portTextField->isClicked())
					{
						portTextField->click();
					}

					if (ipTextField->isClicked())
					{
						ipTextField->click();
					}
					else
					{
						ipTextField->click();
					}
				}

				if ( portTextField->isMouseOver(mousePos) )
				{
					// if ipTextField is clicked then lose focus..
					if (ipTextField->isClicked())
					{
						ipTextField->click();

					}

					if (portTextField->isClicked())
					{
						portTextField->click();
					}
					else
					{
						portTextField->click();
					}
				}
			}

			if (ev.type == sf::Event::TextEntered)
			{
				if (TextEventHelper::isNumber(ev))
				{
					if (ipTextField->isClicked())
						ipTextField->setText(ipTextField->getText() + ev.text.unicode);
					if (portTextField->isClicked())
						portTextField->setText(portTextField->getText() + ev.text.unicode);
				}
				else if (TextEventHelper::isDot(ev))
				{
					// "remove" the possibility to input double dots
					if (ipTextField->isClicked())
						ipTextField->setText(ipTextField->getText() + ev.text.unicode);
				}
				else if (TextEventHelper::isBackspace(ev))
				{
					if (ipTextField->isClicked())
					{
						ipTextField->removeLastCharacter();
					}

					if (portTextField->isClicked())
					{
						portTextField->removeLastCharacter();
					}
				}
			} // end of textentered
		} // end of pollEvent loop
	}
}
