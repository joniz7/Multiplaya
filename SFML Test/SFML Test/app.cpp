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

////////////////////////////////////////////////////////////
/// Application class. Manages the program. The controller,
/// if you so will.
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Initializes the model thread which runs the game logic.
	// Must have a pointer to WorldData instance as argument
	////////////////////////////////////////////////////////////
	void createModelThread(void* UserData)
	{
		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		std::cout<<"Starting logic thread.";
		// Cast to world data pointer
		WorldData* worldData = static_cast<WorldData*>(UserData);
		std::cout<<".";
		// Initialize the model and pass the world data pointer as argument
		World* model = new World(worldData);
		std::cout<<".";
		std::cout<<std::endl<<"Logic thread up and running!"<<std::endl;
		// Unlock world data
		worldDataMutex.unlock();
		model->exec();
	}

	////////////////////////////////////////////////////////////
	// Initializes the view thread which renders the graphics.
	// Must have a pointer to WorldData instance as argument
	////////////////////////////////////////////////////////////
	void createViewThread(void* UserData)
	{
		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		std::cout<<"Starting view thread.";
		// Cast to world data pointer
		WorldData* worldData = static_cast<WorldData*>(UserData);
		std::cout<<".";
		// Initialize the view and pass the world data pointer as argument
		WorldView* view = new WorldView(worldData);
		
		worldData->addObserver(view);

		std::cout<<".";
		std::cout<<std::endl<<"View thread up and running!"<<std::endl;
		// Unlock world data
		worldDataMutex.unlock();
		view->exec();
		//worldData->getCharacter(1)->addObserver(view->getCharacter(0));
	}

	////////////////////////////////////////////////////////////
	// Initializes the network thread which handles sending and receiving data.
	// Must have a pointer to WorldData instance as argument
	////////////////////////////////////////////////////////////
	void createNetworkThread(void* UserData)
	{
		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		std::cout<<"Starting network thread.";
		
		
		// Cast to world data pointer
		WorldData* worldData = static_cast<WorldData*>(UserData);
		std::cout<<".";
		
		
		// Initialize the view and pass the world data pointer as argument
		//NetworkHandler* network = new NetworkHandler(worldData);
		
		//worldData->addObserver(network);

		std::cout<<".";
		std::cout<<std::endl<<"Network thread up and running!"<<std::endl;
		// Unlock world data
		worldDataMutex.unlock();

		//network->exec();

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
		// Initialize world data instance
		worldData = new WorldData();
		// Create and launch the logic thread
		sf::Thread logicThread(&createModelThread, worldData);
		logicThread.launch();
		// Create and launch the view thread
		sf::Thread viewThread(&createViewThread, worldData);
		viewThread.launch();
		//Create and launch the network thread
		sf::Thread networkThread(&createNetworkThread, worldData);
		networkThread.launch();

        // Main loop. Do other things here I guess
        bool running = true;
        /*
		while (running)
        {
			// I'm lonely :(
        }
		*/
        return EXIT_SUCCESS;
    }
}