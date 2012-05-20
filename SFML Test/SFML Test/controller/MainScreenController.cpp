#include "MainScreenController.h"

namespace mp
{
	MainScreenController::MainScreenController(sf::RenderWindow* window, Screen* mainScreen) : IController(window, mainScreen)
	{
		joinButton = mainScreen->getElement("joinButton");
		hostButton = mainScreen->getElement("hostButton");
		exitButton = mainScreen->getElement("exitButton");
	}

	MainScreenController::~MainScreenController()
	{
		//dtor
	}

	void MainScreenController::handleInput()
	{
		// for hover effects
		while (getRenderWindow()->pollEvent(ev))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getRenderWindow());

			getScreen()->hover(mousePos);

			
			if (ev.type == sf::Event::Closed) {
				// Tell our parent to exit the game.
				notifyObservers(Event::EXIT_GAME, 0);
			}
			if ((ev.type == sf::Event::KeyPressed) && (ev.key.code == sf::Keyboard::Escape)) {
				// Tell our parent to exit the game.
				notifyObservers(Event::EXIT_GAME, 0);
			}

			if (ev.type == sf::Event::MouseButtonReleased)
			{
				if ( joinButton->isMouseOver(mousePos) )
				{
					joinButton->click();
					// Change screen in main controller.
					notifyObservers(Event::SHOW_JOIN,0);
				}

				if ( hostButton->isMouseOver(mousePos) )
				{
					hostButton->click();
					networkHandler->setAsServer();
					networkHandler->setAsClient();
					// Change screen in main controller.
					notifyObservers(SHOW_HOST, 0);
				}

				if ( exitButton->isMouseOver(mousePos) )
				{
					// Tell main controller to shut everything down.
					notifyObservers(Event::EXIT_GAME, 0);
				}
				// get button elements and see which hovers
			}
		}
	}
}