#include "MainScreenController.h"

namespace mp
{
	/**
	 * Creates a new controller for the main menu.
	 * @param window the window  to tie the controller to.
	 * @param hostScreen the actual host screen we're controlling.
	 */
	MainScreenController::MainScreenController(sf::RenderWindow* window, Screen* mainScreen) : IController(window, mainScreen)
	{
		joinButton = mainScreen->getGUIElement("joinButton");
		hostButton = mainScreen->getGUIElement("hostButton");
		exitButton = mainScreen->getGUIElement("exitButton");
	}

	MainScreenController::~MainScreenController() {}

	/**
	 * Handles input for the main menu.
	 */
	void MainScreenController::handleInput()
	{
		// for hover effects
		while (getRenderWindow()->pollEvent(ev))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getRenderWindow());
			getScreen()->hover(mousePos);

			if (ev.type == sf::Event::Closed) {
				// Tell our parent to exit the game.
				notifyObservers(EXIT_GAME, 0);
			}
			if ((ev.type == sf::Event::KeyPressed) && (ev.key.code == sf::Keyboard::Escape)) {
				// Tell our parent to exit the game.
				notifyObservers(EXIT_GAME, 0);
			}

			if (ev.type == sf::Event::MouseButtonReleased)
			{
				if ( joinButton->isMouseOver(mousePos) )
				{
					joinButton->click();
					// Change screen in main controller.
					notifyObservers(SHOW_JOIN,0);
				}

				if ( hostButton->isMouseOver(mousePos) )
				{
					hostButton->click();
					// Change screen in main controller.
					notifyObservers(SHOW_HOST, 0);
				}

				if ( exitButton->isMouseOver(mousePos) )
				{
					// Tell main controller to shut everything down.
					notifyObservers(EXIT_GAME, 0);
				}

			}
		}
	} // End of handleInput
}
