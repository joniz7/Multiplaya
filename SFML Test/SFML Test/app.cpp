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

	void createModelThread(void* UserData)
	{
		worldMutex.lock();	// Lock world mutex since we are handling world class
		std::cout<<"Starting logic thread..."<<std::endl;
		// Cast to world pointer
		World* model = static_cast<World*>(UserData);
		model = new World();
		std::cout<<"Logic thread up and running!"<<std::endl;
		worldMutex.unlock(); // Unlock world mutex
		model->exec();
	}

	/*
	void createViewThread(void* UserData)
	{
		std::cout<<"C"<<std::endl;
		WorldData* worldData = static_cast<WorldData*>(UserData);

		//model->getWorldData();
		
		GlobalMutex.lock();
		std::cout<<"C"<<std::endl;
		// Cast to world pointer
		World* model = static_cast<World*>(UserData);
		// Make sure world data has been initialized before creating the view
		
		bool ready = false;
		while(!ready)
		{
			if(model!=NULL)
			{
				WorldData* foo = model->getWorldData();
				if(foo!=NULL)
					ready = true;
			}
		}
		
		// Initialize the view and pass the world data pointer as argument
		WorldView* view = new WorldView( model->getWorldData() );
		std::cout<<"D"<<std::endl;
		GlobalMutex.unlock();
		view->exec();
		
		std::cout<<"D"<<std::endl;
	}
	*/

	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    App::App(sf::VideoMode mode)
    {
		videoMode = mode;
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    App::~App()
    {

    }

	////////////////////////////////////////////////////////////
	// Render window execute function. Starts the game threads
	//
	// \return Application exit code
	////////////////////////////////////////////////////////////
    int App::exec()
    {
		// Create logic which in turn creates the view thread
		sf::Thread logicThread(&createModelThread, model);
		logicThread.launch();

        // Main loop
        bool running = true;
        while (running)
        {
			// I'm lonely :(
        }
        return EXIT_SUCCESS;
    }
}