#include "Controller.h"

namespace mp
{
	Controller::Controller(World* world, Window* window)
	{
		this->window = window;
		this->world = world;
		this->inGame = false;
		renderWindow = window->getRenderWindow();
		
		// Start our title music.
		MusicHandler::instance().chooseSong("title");
		MusicHandler::instance().play();

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
		MainScreenController* mainScreenController = (MainScreenController*) controllers["mainScreen"];
		GameController* gameController = (GameController*) controllers["hostGame"];
		JoinGameController* joinGameController = (JoinGameController*) controllers["joinGame"];

		mainScreenController->setNetworkHandler(network);
		gameController->setNetworkHandler(network);
		joinGameController->setNetworkHandler(network);
	}

	void Controller::exec()
	{													// TODO: change name from HOST_GAME.
		bool inGame = (GameState::getInstance()->getGameState() == GameState::HOST_GAME);

		// Only if we're ingame, run world simulation.
		if (inGame) {
			world->exec();
		}
	
		switch (GameState::getInstance()->getGameState())
		{
			case GameState::MAIN_SCREEN:
				window->drawMainMenu();
				controllers["mainScreen"]->handleInput();
			break;

			case GameState::JOIN_GAME:
				window->drawJoinMenu();
				controllers["joinGame"]->handleInput();
			break;

			// When we're ingame:   (TODO: change name from HOST_GAME)
			case GameState::HOST_GAME:
				window->drawHostMenu();
				controllers["hostGame"]->handleInput();
			break;

			case GameState::SETTINGS_SCREEN:
				window->drawSettingsMenu();
			break;

		} 	
	}
}