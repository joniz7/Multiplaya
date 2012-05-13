////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "../model/world.h"

#include <iostream>

#include "../global.h"
#include "Controller.h"

////////////////////////////////////////////////////////////
/// Controller class. Handles input.
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor. Initializes the world.
	////////////////////////////////////////////////////////////
    Controller::Controller(World* model, WorldView* view)
    {
		this->model = model;
		this->view = view;
		this->network = NULL; 
		this->currentPlayer = new Player();
		this->currentPlayer->setCharacter(model->getWorldData()->getCurrentCharacter());
    }

	void Controller::setNetworkHandler(NetworkHandler* network) {
		this->network = network;	
	}

	////////////////////////////////////////////////////////////
	// The logic loop; updates the game world, runs Box2D etc.
	////////////////////////////////////////////////////////////
    void Controller::exec()
    {
		bool running = true;
		while(running) {
			model->exec();
			currentPlayer->update();
			// Wait until setNetworkHandler() is called.
			while(network == NULL) {}

			if(network->isConnectedToServer()) {
				network->sendCharacterDataToServer();
			}
		}

    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    Controller::~Controller(){}

}