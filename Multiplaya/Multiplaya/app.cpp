////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "app.h"

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

		bool gameThreadFinished;
		bool networkThreadFinished;
	};

	////////////////////////////////////////////////////////////
	/// Initializes the view thread which renders the graphics.
	/// \param UserData - must be of type Container.
	////////////////////////////////////////////////////////////
	void createGameThread(void* UserData)
	{
		worldDataMutex.lock();

		std::cout<< "Starting game thread."<<std::endl;
		
		// Cast to Container pointer.
		Container* data = static_cast<Container*>(UserData);

		// Instantiate everything!
		data->worldData = new WorldData();
		data->model = new World(data->worldData);
		data->view = new Window(data->worldData);
		data->controller = new Controller(data->model, data->view);
		
		// The view should observe WorldData.
		data->worldData->addObserver(data->view->getGameWindow());

		worldDataMutex.unlock();

		// We're done, let the main program continue.
		data->gameThreadFinished = true;
		
		std::cout<<std::endl<<"View thread up and running!"<<std::endl;
		
		while(!data->networkThreadFinished) {}

		// Run the view's infinite loop
		sf::Clock clock;
		while (true)
		{
			float elapsed = clock.getElapsedTime().asSeconds();
			// Execute controller statements (this also runs model and view).
			data->controller->exec();		

			if(elapsed > (1 / 10.f)) 
			{
				clock.restart();

				if(data->network->isClient) 
				{
					data->network->sendCharacterDataToServer();
					//data->network->sendBulletDataToServer();
				}

				if(data->network->isServer)
				{
					data->network->updateAllClients();
				}
			}
			
		}

	}

	////////////////////////////////////////////////////////////
	/// Initializes the network thread which handles the sending and receiving of data.
	/// \param UserData - must be of type Container.
	////////////////////////////////////////////////////////////
	void createNetworkThread(void* UserData)
	{
		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		std::cout<<"Starting network thread."<<std::endl;
		
		// Cast to world data pointer
		Container* data = static_cast<Container*>(UserData);
		data->network = new NetworkHandler(data->worldData, data->model);
		data->controller->setNetworkHandler(data->network);
		// We want to observe worldData.
		data->worldData->addObserver(data->network);
		std::cout<<std::endl<<"Network thread up and running!"<<std::endl;
		//Unlock world data
		worldDataMutex.unlock();
		// We're done, let the main program continue.
		data->networkThreadFinished = true;
		// Start the network loop.
		data->network->exec();
	}

	////////////////////////////////////////////////////////////
	/// Starts the two game threads.
	/// \return Application exit code
	////////////////////////////////////////////////////////////
    int App::exec()
    {
		
		// I guess we're loading stuff here
		ResourceHandler::instance().loadTexture("resources/ui/backgrounds/bg_title0.jpg");
		ResourceHandler::instance().loadTexture("resources/ui/backgrounds/bg_title1.jpg");
		ResourceHandler::instance().loadTexture("resources/ui/backgrounds/bg_title2.jpg");
		ResourceHandler::instance().loadTexture("resources/test/testsprite.png");

		ResourceHandler::instance().loadSound("resources/sound/pistol_fire1.ogg");
		ResourceHandler::instance().loadSound("resources/sound/pistol_reload1.ogg");
		
		// Contains instances of all parts of our program.
		Container* data = new Container();

		// Create and launch the game thread.
		sf::Thread gameThread(&createGameThread, data);
		gameThread.launch();
		// Wait here until it's up and running.
		while(!data->gameThreadFinished) {}

		//Create and launch the network thread
		sf::Thread networkThread(&createNetworkThread, data);
		networkThread.launch();
		// Wait here until it's up and running.
		while(!data->networkThreadFinished) {}

        return EXIT_SUCCESS;
    }
}