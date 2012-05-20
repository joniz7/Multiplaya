#include "HostGameController.h"

namespace mp
{
	HostGameController::HostGameController(sf::RenderWindow* window, Screen* hostScreen) : IController(window, hostScreen)
	{
		//ctor
		cancelButton = hostScreen->getElement("cancelButton");
		hostButton = hostScreen->getElement("hostButton");
		gravityTextField = hostScreen->getElement("gravityTextField");
		portTextField = hostScreen->getElement("portTextField");

		gravityTextClicked = false;
		portTextClicked = false;
	}

	HostGameController::~HostGameController()
	{
		//dtor
	}

	void HostGameController::handleInput()
	{
		while (getRenderWindow()->pollEvent(ev))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getRenderWindow());
			getScreen()->hover(mousePos);

			if (ev.type == sf::Event::MouseButtonReleased)
			{
				
				if( hostButton->isMouseOver(mousePos) )
				{
					hostButton->click();
					notifyObservers(START_GAME, 0);
				}
				
				
				if ( cancelButton->isMouseOver(mousePos) )
				{
					cancelButton->click();
					notifyObservers(SHOW_MAIN_MENU, 0);
				}

				if ( gravityTextField->isMouseOver(mousePos) )
				{
					// lose focus
					if (portTextClicked)
					{
						portTextField->click();
						portTextClicked = false;
					}

					if (gravityTextClicked)
					{
						gravityTextField->click();
						gravityTextClicked = false;
					}
					else
					{
						gravityTextField->click();
						gravityTextClicked = true;
					}
				}

				if ( portTextField->isMouseOver(mousePos) )
				{
					// if ipTextField is clicked then lose focus..
					if (gravityTextClicked)
					{
						gravityTextField->click();
						gravityTextClicked = false;
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
				/*if (isNumber(ev))
				{
					if (gravityTextClicked)
						gravityTextField->setText(ipTextField->getText() + ev.text.unicode);
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
				}*/
			} // end of textentered

	}
	}
	}