////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "app.h"

// Other headers
#include <string>
#include <cstdlib>
#include <list>

// SFML specific headers
#include "sfml.h"
// Box2D specific headers
#include <Box2D.h>
// Game specific headers
#include "game.h"
// Defines
#include "defines.h"
#include "global.h"

#include "controller/Controller.h"
#include "model/World.h"
#include "view/Window.h"

////////////////////////////////////////////////////////////
/// Application class. Manages the program.
////////////////////////////////////////////////////////////

namespace mp
{
	// Contains instances of all parts of our program.
	struct Container {
		World* model;
		WorldData* worldData;
		Controller* controller;
		Window* view;
		NetworkHandler* network;

		bool viewThreadFinished;
		bool logicThreadFinished;
		bool networkThreadFinished;
	};
	
	////////////////////////////////////////////////////////////
	/// \brief Initializes the controller/model thread which runs the game logic.
	/// \param UserData - must be of type Container.
	////////////////////////////////////////////////////////////
	void createLogicThread(void* UserData)
	{
		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		std::cout<<"Starting controller/model thread."<<std::endl;
		// Cast to controller pointer
		Container* data = static_cast<Container*>(UserData);
		// Instantiate model and controller.
		// (Expects worldData and view to already exist)
		data->model = new World(data->worldData);
		worldDataMutex.unlock();
		// We're done, let the main program continue.
		data->logicThreadFinished = true;
		data->model->exec();
	}

	////////////////////////////////////////////////////////////
	/// Initializes the view thread which renders the graphics.
	/// \param UserData - must be of type Container.
	////////////////////////////////////////////////////////////
	void createViewThread(void* UserData)
	{
		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		std::cout<< "Starting view thread.";
		// Cast to world data pointer
		Container* data = static_cast<Container*>(UserData);
		std::cout<<".";
		data->view = new Window(data->worldData);
		data->controller = new Controller(data->model, data->view);
		// We want to observe WorldData.
		data->worldData->addObserver(data->view->getGameWindow());
		std::cout<<std::endl<<"View thread up and running!"<<std::endl;
		// Unlock world data
		worldDataMutex.unlock();
		// We're done, let the main program continue.
		data->viewThreadFinished = true;
		// Run the view's infinite loop
		while (true)
		{
			data->view->exec();
			data->controller->exec();
		}

	}

	////////////////////////////////////////////////////////////
	/// Initializes the network thread which handles sending and receiving data.
	/// \param UserData - must be of type Container.
	////////////////////////////////////////////////////////////
	void createNetworkThread(void* UserData)
	{
		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		std::cout<<"Starting network thread.";
		
		// Cast to world data pointer
		Container* data = static_cast<Container*>(UserData);
		std::cout<<".";
		data->network = new NetworkHandler(data->worldData, data->model);
		data->controller->setNetworkHandler(data->network);
		// We want to observe worldData.
		data->worldData->addObserver(data->network);
		std::cout<<std::endl<<"Network thread up and running!"<<std::endl;
		//Unlock world data
		worldDataMutex.unlock();
		// We're done, let the main program continue.
		data->networkThreadFinished = true;
		data->network->exec();
	}

	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    App::App(sf::VideoMode mode){videoMode = mode;}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    App::~App(){}

	////////////////////////////////////////////////////////////
	// Render window execute function. Starts the game threads
	//
	// \return Application exit code
	////////////////////////////////////////////////////////////
    int App::exec()
    {
		// Contains instances of all parts of our program.
		Container* data = new Container();
		
		// Instantiate everything!
		data->worldData = new WorldData();

		// Create and launch the logic thread.
		// Important: depends on viewThread already being launched!
		sf::Thread logicThread(&createLogicThread, data);
		logicThread.launch();
		while(!data->logicThreadFinished) {}

		// Create and launch the view thread.
		sf::Thread viewThread(&createViewThread, data);
		viewThread.launch();
		while(!data->viewThreadFinished) {}


		//Create and launch the network thread
		sf::Thread networkThread(&createNetworkThread, data);
		networkThread.launch();
		while(!data->networkThreadFinished) {}

        return EXIT_SUCCESS;
    }
}