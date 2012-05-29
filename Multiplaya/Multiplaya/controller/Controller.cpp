#include "Controller.h"

namespace mp
{
	/**
	 * Creates a new controller.
	 * @param world the model to use.
	 * @param window the view to use.
	 */
	Controller::Controller(World* world, Window* window)
	{
		this->window = window;
		this->world = world;
		renderWindow = window->getRenderWindow();

		// Create our minion controllers.
		controllers["mainScreen"] = new MainScreenController(renderWindow, window->getScreen("mainScreen"));
		controllers["pauseScreen"] =  new PauseScreenController(renderWindow, window->getScreen("pauseScreen"));
		controllers["joinGame"] = new JoinGameController(renderWindow, window->getScreen("joinGameScreen"));
		controllers["game"] =  new GameController(world, renderWindow, window->getScreen("gameScreen"));

		// Add ourselves as observer.
		controllers["mainScreen"]->addObserver(this);
		controllers["pauseScreen"]->addObserver(this);
		controllers["joinGame"]->addObserver(this);
		controllers["game"]->addObserver(this);
		runGame = false;
		// Begin at main menu.
		this->notify(SHOW_MAIN_MENU, 0);

	}

	/**
	 * Notify the controller of any state changes.
	 * This is used to change screens and exit the game.
	 */
	void Controller::notify(Event e, void* object) {
		switch (e) {
			case START_GAME:     startGame();        break;
			case EXIT_GAME:      exitGame();         break;
			case PAUSE_GAME:     pauseGame();        break;
			case RESUME_GAME:    resumeGame();       break;
			case SHOW_JOIN:      showJoinMenu();     break;
			case SHOW_MAIN_MENU: showMainMenu();     break;
			default: break;
		}
	}

	void Controller::startGame() {
		// Start our ingame music.
		this->runGame = true;
		MusicHandler::instance().chooseSong("bg");
		MusicHandler::instance().play();

		window->getRenderWindow()->setMouseCursorVisible(false);
		this->currentDrawFunction = &Window::drawGame;
		this->currentController = controllers["game"];
	}

	void Controller::exitGame() {
		this->runGame = false;
		exit(0);
	}

	void Controller::pauseGame(){
		this->currentDrawFunction = &Window::drawPauseMenu;
		this->currentController = controllers["pauseScreen"];
		};

	void Controller::resumeGame(){
		// Set pointers.
		this->currentDrawFunction = &Window::drawGame;
		this->currentController = controllers["game"];
	}

	void Controller::showMainMenu(){
		// If we're coming  from ingame, reset game world.
		if (runGame) {
			this->reset();
		}
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

	void Controller::reset() {
		// Reset model.
		world->reset();
		
		// Reset GameController.
		((GameController*) controllers["game"])->reset();

		// Reset view
		window->getGameWindow()->reset();
	}

	Controller::~Controller()
	{
		//dtor
	}

	/**
	 * Sets which NetworkHandler the game should use.
	 */
	void Controller::setNetworkHandler(NetworkHandler* network) {
		MainScreenController* mainScreenController = (MainScreenController*) controllers["mainScreen"];
		mainScreenController->setNetworkHandler(network);

		GameController* gameController = (GameController*) controllers["game"];
		gameController->setNetworkHandler(network);

		JoinGameController* joinGameController = (JoinGameController*) controllers["joinGame"];
		joinGameController->setNetworkHandler(network);
	}

	/**
	 * Runs the whole game.
	 * Executes game logic, handles input and draws everything to screen.
	 */
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
