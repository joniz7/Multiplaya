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

		bool viewThreadFinished;
		bool logicThreadFinished;
		bool networkThreadFinished;
	};

	////////////////////////////////////////////////////////////
	/// Initializes the view thread which renders the graphics.
	/// \param UserData - must be of type Container.
	////////////////////////////////////////////////////////////
	void createViewThread(void* UserData)
	{
		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		std::cout<< "Starting view thread."<<std::endl;
		// Cast to world data pointer
		Container* data = static_cast<Container*>(UserData);

		// Instantiate everything!
		data->worldData = new WorldData();
		data->model = new World(data->worldData);
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
		sf::Clock clock;
		
		while (true)
		{
			float elapsed = clock.getElapsedTime().asSeconds();
			data->controller->exec();
			
			if(elapsed>(1/20.f))
			{
				clock.restart();
				if(data->network->isServer)
				{
					data->network->updateAllClients();
				}
			
				if(data->network->isClient) 
				{
					data->network->sendCharacterDataToServer();
				}
			}
			
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
		data->network->exec();
	}

	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    //App::App(sf::VideoMode mode) { videoMode = mode; }
	App::App() { }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    App::~App(){}

	////////////////////////////////////////////////////////////
	/// Starts the two game threads.
	/// \return Application exit code
	////////////////////////////////////////////////////////////
    int App::exec()
    {
		// Contains instances of all parts of our program.
		Container* data = new Container();

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