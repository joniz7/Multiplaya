#include "Controller.h"

namespace mp
{
	Controller::Controller(World* world, Window* window)
	{
		//ctor
		this->window = window;
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

	void Controller::initTitleMusic() {

		/*
		std::string resourcesDir = ConfigHandler::instance().getString("s_resourcesdir");
		std::cout << "resourcesDir: "<<resourcesDir<<std::endl;

		titleMusic = new sf::Music();

		// Generate random number between 1 and 10.
		srand ( time(NULL) );
		int songNumber = rand() % 10 + 1;
		// generate path to .ogg-file.
		std::stringstream path;
		path << resourcesDir << "bgmusic-" << songNumber << ".ogg";
		// Open it from an audio file.
		if (!titleMusic->openFromFile(path.str())) {
			std::cout << "Failed to load titleMusic: "+path.str() << std::endl;
		}
		else {
			std::cout << "Playing song #"<<songNumber<<". Rock on!" << std::endl;
		}

		 //titleMusic->setPosition(0, 1, 10); // change its 3D position
		 //titleMusic->setPitch(1);           // increase the pitch
		 //titleMusic->setVolume(50);         // reduce the volume
		 titleMusic->setLoop(true);         // make it loop
		 // Play it
		 titleMusic->play();
		 */

	}
}