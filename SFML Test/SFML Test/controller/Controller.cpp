#include "Controller.h"

namespace mp
{
	Controller::Controller(World* world, Window* window)
	{
		//ctor
		this->window = window;
		renderWindow = window->getRenderWindow();

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
		switch (GameState::getInstance()->getGameState())
		{
			case GameState::MAIN_SCREEN:
				controllers["mainScreen"]->handleInput();
			break;

			case GameState::JOIN_GAME:
				controllers["joinGame"]->handleInput();
			break;

			case GameState::HOST_GAME:
				controllers["hostGame"]->handleInput();
			break;

			case GameState::SETTINGS_SCREEN:

			break;
		} 	
	}
}