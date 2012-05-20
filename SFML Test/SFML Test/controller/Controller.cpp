#include "Controller.h"

namespace mp
{
	Controller::Controller(World* world, Window* window)
	{
		this->window = window;
		this->world = world;
		this->runGame = false;
		this->state = MAIN_MENU;
		renderWindow = window->getRenderWindow();
		
		// Start our menu music.
		MusicHandler::instance().chooseSong("menu");
		MusicHandler::instance().play();

		// Create our minion controllers.
		controllers["mainScreen"] = new MainScreenController(renderWindow, window->getScreen("mainScreen"));
		controllers["joinGame"] = new JoinGameController(renderWindow, window->getScreen("joinGameScreen"));
		controllers["hostGame"] =  new GameController(world, renderWindow, window->getScreen("hostScreen"));
		//controllers["worldScreen"] =
		//new HostGameController(renderWindow, window->getScreen("hostScreen"));

		// We're going to observe their every move.
		// ...
		// One Ring to rule them all, One Ring to find them,
		// One Ring to bring them all and in the darkness bind them.
		controllers["mainScreen"]->addObserver(this);
		controllers["joinGame"]->addObserver(this);
		controllers["hostGame"]->addObserver(this);
		//controllers["worldScreen"]->addObserver(this);
	}

	void Controller::notify(Event e, void* object) {
		std::cout << "Notified! Message: ";
		switch (e) {
			case START_GAME:
				std::cout << "START_GAME" << std::endl;
				// TODO: reset everything here.

				// Start our ingame music.
				MusicHandler::instance().chooseSong("bg");
				MusicHandler::instance().play();
				this->runGame = true;
				//this->state = INGAME;
				break;

				case STOP_GAME:
				std::cout << "STOP_GAME" << std::endl;
				this->runGame = false;
				this->state = MAIN_MENU;
				break;

			case EXIT_GAME:
				std::cout << "EXIT_GAME" << std::endl;
				// TODO: kill process here.
				break;

			case PAUSE_GAME:
				std::cout << "PAUSE_GAME" << std::endl;
				//this->state = INGAME_MENU;
				this->state = MAIN_MENU;
				break;

			case RESUME_GAME:
				std::cout << "RESUME_GAME" << std::endl;
				//this->state = INGAME;
				this->state = HOST_MENU;
				break;

			case SHOW_HOST:
				std::cout << "SHOW_HOST" << std::endl;
				//  --- TODO: remove ---
				// Start our ingame music.
				MusicHandler::instance().chooseSong("bg");
				MusicHandler::instance().play();
				this->runGame = true;
				// ---------------------
				this->state = HOST_MENU;
				break;

			case SHOW_JOIN:
				std::cout << "SHOW_JOIN" << std::endl;
				this->state = JOIN_MENU;
				break;

			case SHOW_MAIN_MENU:
				std::cout << "SHOW_MAIN_MENU" << std::endl;
				
				// Start our menu music.
				MusicHandler::instance().chooseSong("menu");
				MusicHandler::instance().play();
				this->state = MAIN_MENU;
				break;

			case SHOW_SETTINGS:
				std::cout << "SHOW_SETTINGS" << std::endl;
				//this->state = SETTINGS_MENU;
				break;
		}
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
	{
		// Only if we're ingame, run world simulation.
		if (runGame) {
			world->exec();
		}
	
		switch (this->state)
		{
			case MAIN_MENU:
				window->drawMainMenu();
				controllers["mainScreen"]->handleInput();
			break;

			case JOIN_MENU:
				window->drawJoinMenu();
				controllers["joinGame"]->handleInput();
			break;
			
			// The actual ingame (for now):
			case HOST_MENU:
				window->drawHostMenu();
				controllers["hostGame"]->handleInput();
				break;
				
			case INGAME:
				// TODO: implement
				//window->drawInGame();
				//controllers["inGame"]->handleInput();
				break;

			case INGAME_MENU:
				// TODO: implement
				//window->drawInGameMenu();
				//controllers["inGameMenu"]->handleInput();
				break;

		} 	
	}
}