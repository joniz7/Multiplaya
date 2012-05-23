#include "PauseScreenController.h"

namespace mp
{
	/**
	 * Creates a new controller for the pause screen.
	 * @param window the window  to tie the controller to.
	 * @param hostScreen the actual host screen we're controlling.
	 */
	PauseScreenController::PauseScreenController(sf::RenderWindow* window, Screen* mainScreen) : IController(window, mainScreen)
	{
		resumeButton = mainScreen->getGUIElement("resumeButton");
		disconnectButton = mainScreen->getGUIElement("disconnectButton");
		exitButton = mainScreen->getGUIElement("exitButton");
	}

	PauseScreenController::~PauseScreenController() {}

	/**
	 * Handles input for the pause menu.
	 */
	void PauseScreenController::handleInput()
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
				getRenderWindow()->setMouseCursorVisible(false);
				// Tell our parent to resume the game.
				notifyObservers(RESUME_GAME, 0);
			}

			if (ev.type == sf::Event::MouseButtonReleased)
			{
				if ( resumeButton->isMouseOver(mousePos) )
				{
					getRenderWindow()->setMouseCursorVisible(false);
					resumeButton->click();
					// Change screen in main controller.
					notifyObservers(RESUME_GAME,0);
				}

				if ( disconnectButton->isMouseOver(mousePos) )
				{
					disconnectButton->click();
					// Change screen in main controller.
					notifyObservers(SHOW_MAIN_MENU, 0); // TODO event DISCONNECT ?
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
