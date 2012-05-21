#include "HostGameController.h"

namespace mp
{
	HostGameController::HostGameController(sf::RenderWindow* window, Screen* hostScreen) : IController(window, hostScreen)
	{
		//ctor
		cancelButton = hostScreen->getElement("cancelButton");
		hostButton = hostScreen->getElement("hostButton");
		gravityTextField = (TextField*) hostScreen->getElement("gravityTextField");
		portTextField = (TextField*) hostScreen->getElement("portTextField");
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
					networkHandler->setAsServer();
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
					if (portTextField->isClicked())
					{
						portTextField->click();
					}

					if (gravityTextField->isClicked())
					{
						gravityTextField->click();
					}
					else
					{
						gravityTextField->click();
					}
				}

				if ( portTextField->isMouseOver(mousePos) )
				{
					// if ipTextField is clicked then lose focus..
					if (gravityTextField->isClicked())
					{
						gravityTextField->click();

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
					if (gravityTextField->isClicked())
						gravityTextField->setText(gravityTextField->getText() + ev.text.unicode);
					if (portTextField->isClicked())
						portTextField->setText(portTextField->getText() + ev.text.unicode);
				}
				else if (TextEventHelper::isDot(ev))
				{
					// "remove" the possibility to input double dots
					if (gravityTextField->isClicked())
						gravityTextField->setText(gravityTextField->getText() + ev.text.unicode);

				}
				else if (TextEventHelper::isBackspace(ev))
				{
					if (gravityTextField->isClicked())
					{
						gravityTextField->removeLastCharacter();
					}
						
					if (portTextField->isClicked())
					{
						portTextField->removeLastCharacter();
					}	
				}
			} // end of textentered
		}
	} // end of handeInput

}