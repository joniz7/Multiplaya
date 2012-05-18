////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header

#include "GameController.h"

////////////////////////////////////////////////////////////
/// Controller class. Handles input.
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor. Initializes the world.
	////////////////////////////////////////////////////////////
    GameController::GameController(World* model, sf::RenderWindow* window, Screen* gameScreen) : IController(window, gameScreen)
    {
		worldView = (WorldView*) gameScreen;
		this->model = model;
		this->network = NULL; 
		this->currentPlayer = new Player();
		worldDataMutex.unlock();
		this->currentPlayer->setCharacter(model->getWorldData()->getCurrentCharacter());
		worldDataMutex.lock();
    }

	void GameController::setNetworkHandler(NetworkHandler* network) {
		this->network = network;	
	}

	////////////////////////////////////////////////////////////
	// The logic loop; updates the game world, runs Box2D etc.
	////////////////////////////////////////////////////////////
    void GameController::handleInput()
    {
		sf::Vector2f mousePos = getRenderWindow()->convertCoords(sf::Mouse::getPosition(*getRenderWindow()), *worldView->getCamera());
		currentPlayer->update(mousePos);

		// Wait until setNetworkHandler() is called.
		while(network == NULL) {}

		if(network->isConnectedToServer()) {
			network->sendCharacterDataToServer();
		}

		while (getRenderWindow()->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				getRenderWindow()->close();
			if ((ev.type == sf::Event::KeyPressed) && (ev.key.code == sf::Keyboard::Escape))
				getRenderWindow()->close();

			// Handle zooming of viewport
			if ( ev.type == sf::Event::MouseWheelMoved )
			{
				if( ev.mouseWheel.delta > 0)
					worldView->zoom(0.9f);
				else
					worldView->zoom(1.1f);
			}
		}
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    GameController::~GameController(){}

}