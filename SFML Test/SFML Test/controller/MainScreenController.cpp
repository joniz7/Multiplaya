#include "MainScreenController.h"

namespace mp
{
	MainScreenController::MainScreenController(sf::RenderWindow* window, Screen* mainScreen) : IController(window, mainScreen)
	{
		joinButton = mainScreen->getElement("joinButton");
		hostButton = mainScreen->getElement("hostButton");
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

			if (ev.type == sf::Event::MouseButtonReleased)
			{
				if ( joinButton->isMouseOver(mousePos) )
				{
					joinButton->click();
					GameState::getInstance()->setGameState(GameState::JOIN_GAME);
				}

				if ( hostButton->isMouseOver(mousePos) )
				{
					hostButton->click();
					GameState::getInstance()->setGameState(GameState::HOST_GAME);
				}
				// get button elements and see which hovers
			}
		}
	}
}