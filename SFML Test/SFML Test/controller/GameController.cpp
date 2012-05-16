////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "../model/world.h"

#include <iostream>

#include "../global.h"
#include "GameController.h"
#include "../view/worldview.h"

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
		this->model = model;
		this->network = NULL; 
		this->currentPlayer = new Player();
		this->currentPlayer->setCharacter(model->getWorldData()->getCurrentCharacter());
    }

	void GameController::setNetworkHandler(NetworkHandler* network) {
		this->network = network;	
	}

	////////////////////////////////////////////////////////////
	// The logic loop; updates the game world, runs Box2D etc.
	////////////////////////////////////////////////////////////
    void GameController::handleInput(sf::Event &ev)
    {
		currentPlayer->update();

		// Handle zooming of viewport
		if ( ev.type == sf::Event::MouseWheelMoved )
		{
			if( ev.mouseWheel.delta > 0)
				( (WorldView*) getScreen() )->zoom(0.9f);
			else
				( (WorldView*) getScreen() )->zoom(1.1f);
			
		}

		// Wait until setNetworkHandler() is called.
		while(network == NULL) {}

		if(network->isConnectedToServer()) {
			network->sendCharacterDataToServer();
		}
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    GameController::~GameController(){}

}