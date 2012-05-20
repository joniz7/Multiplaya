#include "Controller.h"

namespace mp
{
	Controller::Controller(World* world, Window* window)
	{
		this->window = window;
		this->world = world;
		renderWindow = window->getRenderWindow();

		// Create our minion controllers.
		controllers["mainScreen"] = new MainScreenController(renderWindow, window->getScreen("mainScreen"));
		controllers["joinGame"] = new JoinGameController(renderWindow, window->getScreen("joinGameScreen"));
		controllers["game"] =  new GameController(world, renderWindow, window->getScreen("gameScreen"));
		controllers["hostGame"] =  new HostGameController(renderWindow, window->getScreen("hostScreen"));

		//controllers["worldScreen"] =
		//new HostGameController(renderWindow, window->getScreen("hostScreen"));

		// Add ourselves as observer.
		controllers["mainScreen"]->addObserver(this);
		controllers["joinGame"]->addObserver(this);
		controllers["hostGame"]->addObserver(this);
		controllers["game"]->addObserver(this);
		//controllers["worldScreen"]->addObserver(this);
		runGame = false;
		// Begin at main menu.
		this->notify(Event::SHOW_MAIN_MENU, 0);

	}


	void Controller::notify(Event e, void* object) {
		switch (e) {
			case START_GAME:     startGame();        break;
			case STOP_GAME:      stopGame();         break;
			case EXIT_GAME:      exitGame();         break;
			case PAUSE_GAME:     pauseGame();        break;
			case RESUME_GAME:    resumeGame();       break;
			case SHOW_HOST:      showHostMenu();     break;
			case SHOW_JOIN:      showJoinMenu();     break;
			case SHOW_MAIN_MENU: showMainMenu();     break;
			case SHOW_SETTINGS:  showSettingsMenu(); break;
		}
	}

	void Controller::startGame() {
		// TODO: reset everything here.
		// Start our ingame music.
		this->runGame = true;
		MusicHandler::instance().chooseSong("bg");
		MusicHandler::instance().play();
		// TODO: replace with "inGame"
		this->currentDrawFunction = &Window::drawGame;
		this->currentController = controllers["game"];
		
	}
	void Controller::stopGame() {
		this->runGame = false;
		// TODO: replace with "inGame"
		this->currentDrawFunction = &Window::drawMainMenu;
		this->currentController = controllers["mainScreen"];
	}
	void Controller::exitGame() {
		this->runGame = false;
		exit(0); // TODO: exit properly?
	}

	void Controller::pauseGame(){
		// TODO: replace with "inGameMenu".
		this->currentDrawFunction = &Window::drawMainMenu;
		this->currentController = controllers["mainScreen"];
		};
	
	void Controller::resumeGame(){
		// Set pointers.
		this->currentDrawFunction = &Window::drawGame;
		this->currentController = controllers["game"];
	}
			
	void Controller::showMainMenu(){
		// Start our menu music.
		MusicHandler::instance().chooseSong("menu");
		MusicHandler::instance().play();
		// Set pointers.
		this->currentDrawFunction = &Window::drawMainMenu;
		this->currentController = controllers["mainScreen"];
	}
			
	void Controller::showJoinMenu(){
		// Set pointers.
		this->currentDrawFunction = &Window::drawJoinMenu;
		this->currentController = controllers["joinGame"];
	}
			
	void Controller::showHostMenu(){
		// Set pointers.
		this->currentDrawFunction = &Window::drawHostMenu;
		this->currentController = controllers["hostGame"];
	}

	void Controller::showSettingsMenu(){
		// Set pointers.
		//this->currentDrawFunction = &Window::drawSettingsMenu;
		//this->currentController   = controllers["settingsScreen"];
	}


	Controller::~Controller()
	{
		//dtor
	}

	void Controller::setNetworkHandler(NetworkHandler* network) {
		MainScreenController* mainScreenController = (MainScreenController*) controllers["mainScreen"];
		GameController* gameController = (GameController*) controllers["game"];
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
		
		(window->*currentDrawFunction)(); // Draw screen.
		currentController->handleInput(); // Handle input.
	}
}