#include "Controller.h"

namespace mp
{
	Controller::Controller(World* world, Window* window)
	{
		//ctor
		this->window = window;
		renderWindow = window->getRenderWindow();
		ev = new sf::Event();

		controllers["mainScreen"] = new MainScreenController(renderWindow, window->getScreen("mainScreen"));
		controllers["joinGame"] = new JoinGameController(renderWindow, window->getScreen("joinGameScreen"));
	  //  controllers["hostGame"] = new HostGameController();
		controllers["hostGame"] = new GameController(world, renderWindow, window->getScreen("hostScreen"));
	}

	Controller::~Controller()
	{
		//dtor
	}

	void Controller::setNetworkHandler(NetworkHandler* network) {
		GameController* gameController = (GameController*) controllers["hostGame"];
		gameController->setNetworkHandler(network);
	}

	void Controller::exec()
	{
		while (window->getRenderWindow()->pollEvent(*ev))
		{
			if (ev->type == sf::Event::Closed)
				renderWindow->close();
			if ((ev->type == sf::Event::KeyPressed) && (ev->key.code == sf::Keyboard::Escape))
				renderWindow->close();

			switch (GameState::getInstance()->getGameState())
			{
				case GameState::MAIN_SCREEN:
					controllers["mainScreen"]->handleInput(*ev);
				break;

				case GameState::JOIN_GAME:
					controllers["joinGame"]->handleInput(*ev);
				break;

				case GameState::HOST_GAME:
					controllers["hostGame"]->handleInput(*ev);
				break;

				case GameState::SETTINGS_SCREEN:

				break;
			} 
		}
	}
}