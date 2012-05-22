////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////
#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include <SFML/Window.hpp>

// Box2D specific headers
#include <Box2D.h>

// Defines
#include "../services/networkhandler.h"
#include "../defines.h"
#include "../controller/Player.h"
#include "IController.h"
#include "../view/screens/worldview.h"

#include "../model/world.h"

#include <iostream>

#include "../global.h"

#include "../view/screens/worldview.h"

namespace mp
{
	//Forward declaration so World can have a WorldData pointer
	class World;

	/**
	 * The controller for when we're ingame.
	 */
    class GameController : public IController
    {
        public:
			GameController(World* model, sf::RenderWindow* window, Screen* joinGameScreen);
			~GameController();
			void handleInput();
			void setNetworkHandler(NetworkHandler* network);
            

        private:
			World* model; ///< The model for the game.
			WorldView* worldView; ///< The game's view.
			// TODO: not sure if all controller classes should own a sf::event instanec
			sf::Event ev;

			Player* currentPlayer;
			NetworkHandler* network;

			float zoomFactor;
    };
}

#endif
