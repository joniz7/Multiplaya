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
		
		worldDataMutex.lock();
		this->currentPlayer->setCharacter(model->getWorldData()->getCurrentCharacter());
		worldDataMutex.unlock();

		zoomFactor = 0;
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
			{
				GameState::getInstance()->setGameState(GameState::MAIN_SCREEN);
				getRenderWindow()->setMouseCursorVisible(true);
			}


			// Handle zooming of viewport
			if ( ev.type == sf::Event::MouseWheelMoved ) {
				if( ev.mouseWheel.delta > 0 && zoomFactor >= -0.7f) {
					std::cout << zoomFactor << std::endl;
					worldView->zoom(1/1.1f);
					zoomFactor -= 0.1f;
				}
				else if (ev.mouseWheel.delta < 0 && zoomFactor <= 0.1f) {
					std::cout << zoomFactor << std::endl;
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
