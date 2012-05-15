#include "MainScreenController.h"

namespace mp
{
	MainScreenController::MainScreenController(sf::RenderWindow* window, Screen* mainScreen) : IController(window, mainScreen)
	{
		joinButton = mainScreen->getElement("joinButton");
	}

	MainScreenController::~MainScreenController()
	{
		//dtor
	}

	void MainScreenController::handleInput(sf::Event &ev)
	{
		// for hover effects
		sf::Vector2i mousePos = sf::Mouse::getPosition(*getRenderWindow());
		getScreen()->hover(mousePos);

		if (ev.type == sf::Event::MouseButtonReleased)
		{
			if ( joinButton->isMouseOver(mousePos) )
			{
				joinButton->click();
				GameState::getInstance()->setGameState(GameState::JOIN_GAME);
			}

			// get button elements and see which hovers
		}
	}
}