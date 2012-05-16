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
#include "../sfml.h"

// Box2D specific headers
#include <Box2D.h>

// Defines
#include "../services/networkhandler.h"
#include "../defines.h"
#include "../controller/Player.h"
#include "IController.h"
#include "../view/worldview.h"

#include "../model/world.h"

#include <iostream>

#include "../global.h"

namespace mp
{
	//Forward declaration so World can have a WorldData pointer
	class World;

    class GameController : public IController
    {
        public:
			GameController(World* model, sf::RenderWindow* window, Screen* joinGameScreen);
			~GameController();
			void handleInput();
			void setNetworkHandler(NetworkHandler* network);
            

        private:
			World* model;
			// temporary, better solution will be found!
			WorldView* worldView;
			// not sure if all controller classes should own a sf::event instanec
			sf::Event ev;

			Player* currentPlayer;
			NetworkHandler* network;
    };
}

#endif
