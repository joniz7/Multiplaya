// Class header
#include "app.h"

namespace mp
{
	/**
	 * Contains instances of all parts of our program.
	 */
	struct Container {
		World* model;
		WorldData* worldData;
		Controller* controller;
		Window* view;
		NetworkHandler* network;

		bool gameThreadFinished;
		bool networkThreadFinished;
	};

	/** 
	 * Initializes the network thread, which handles the sending and receiving of data.
	 * @param UserData - must be of type Container.
	 */
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

	/**
	 * Starts the network thread, and runs the game loop.
	 * @return Application exit code
	 */
    int App::exec()
    {
		// Nothing to see here. Just loading some resources.
		ResourceHandler::instance().loadTexture("resources/ui/backgrounds/bg_title0.jpg");
		ResourceHandler::instance().loadTexture("resources/ui/backgrounds/bg_title1.jpg");
		ResourceHandler::instance().loadTexture("resources/ui/backgrounds/bg_title2.jpg");
		ResourceHandler::instance().loadTexture("resources/test/testsprite.png");

		ResourceHandler::instance().loadSound("resources/sound/pistol_fire1.ogg");
		ResourceHandler::instance().loadSound("resources/sound/pistol_reload1.ogg");
		ResourceHandler::instance().loadSound("resources/sound/char_jump.ogg");
		
		// Contains instances of all parts of our program.
		Container* data = new Container();
		
		// Instantiate all parts of the program.
		data->worldData = new WorldData();
		data->model = new World(data->worldData);
		data->view = new Window(data->worldData);
		data->controller = new Controller(data->model, data->view);
		
		worldDataMutex.lock();

		std::cout<< "Starting game thread... "<<std::endl;

		// The view should observe WorldData.
		data->worldData->addObserver(data->view->getGameWindow());

		worldDataMutex.unlock();

		std::cout<<std::endl<<"Game thread up and running!"<<std::endl;
		
		//Create and launch the network thread.
		sf::Thread networkThread(&createNetworkThread, data);
		networkThread.launch();
		// Wait here until it's up and running.
		while(!data->networkThreadFinished) {}
		
		// Run the main loop of the program.
		sf::Clock clock;
		while (true) {
			float elapsed = clock.getElapsedTime().asSeconds();
			// Execute controller statements (this also runs model and view).
			data->controller->exec();		

			if(elapsed > (1 / 10.f)) {
				clock.restart();

				if(data->network->isClient) {
					data->network->sendCharacterDataToServer();
					//data->network->sendBulletDataToServer();
				}

				if(data->network->isServer) {
					data->network->updateAllClients();
				}
			}
			
		}

        return EXIT_SUCCESS;
    }
}