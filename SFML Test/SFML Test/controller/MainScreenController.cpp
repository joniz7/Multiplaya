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

			
			if (ev.type == sf::Event::Closed)
				getRenderWindow()->close();
			if ((ev.type == sf::Event::KeyPressed) && (ev.key.code == sf::Keyboard::Escape))
				getRenderWindow()->close();

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
					getRenderWindow()->setMouseCursorVisible(false);
					GameState::getInstance()->setGameState(GameState::HOST_GAME);
				}

				if ( exitButton->isMouseOver(mousePos) )
				{
					getRenderWindow()->close();
				}
				// get button elements and see which hovers
			}
		}
	}
}