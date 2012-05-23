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
	/**
	 * Creates a new controller for ingame movements.
	 * @param window the window  to tie the controller to.
	 * @param hostScreen the actual host screen we're controlling.
	 */
    GameController::GameController(World* model, sf::RenderWindow* window, Screen* gameScreen) : IController(window, gameScreen)
    {
		worldView = (WorldView*) gameScreen;
		this->model = model;
		this->network = NULL;
		this->currentPlayer = new Player();

		worldDataMutex.lock();
		this->currentPlayer->setCharacter(model->getWorldData()->getCurrentCharacter());
		worldDataMutex.unlock();

		zoomFactor = 0;
    }

	void GameController::setNetworkHandler(NetworkHandler* network) 
	{
		this->network = network;
	}


	/**
	 * Handles input for when we're ingame.
	 */
    void GameController::handleInput()
    {
		sf::Vector2i mousePosWindow = sf::Mouse::getPosition(*getRenderWindow());
		((WorldView*)getScreen())->setMousePos(mousePosWindow);

		sf::Vector2f mousePos = getRenderWindow()->convertCoords(mousePosWindow, *worldView->getCamera());
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
			{
				// Change screen in main controller.
				notifyObservers(PAUSE_GAME,0);
				getRenderWindow()->setMouseCursorVisible(true);
			}

			if( sf::Keyboard::isKeyPressed( sf::Keyboard::F5 ) )
		{
			std::cout<<"Updating world geo view"<<std::endl;
			((WorldView*)getScreen())->updateWorldVertices();
		}


			// Handle zooming of viewport
			if ( ev.type == sf::Event::MouseWheelMoved ) {
				if( ev.mouseWheel.delta > 0 && zoomFactor >= -0.7f) {
					worldView->zoom(1/1.1f);
					zoomFactor -= 0.1f;
				}
				else if (ev.mouseWheel.delta < 0 && zoomFactor <= 0.1f) {
					worldView->zoom(1.1f);
					zoomFactor += 0.1f;
				}
			}
		}
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    GameController::~GameController(){}

}
