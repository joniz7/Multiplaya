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
		// Lock world
		worldMutex.lock();
		std::cout<<"Starting logic thread..."<<std::endl;
		// Cast to world pointer
		World* model = static_cast<World*>(UserData);
		model = new World();
		std::cout<<"Logic thread up and running!"<<std::endl;
		// Unlock world
		worldMutex.unlock();
		model->exec();
	}

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