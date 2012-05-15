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

// Game specific headers
#include "../game.h"

// Defines
#include "../defines.h"
#include "../controller/Player.h"
#include "IController.h"

namespace mp
{
	//Forward declaration so World can have a WorldData pointer
	class World;

    class GameController : public IController
    {
        public:
			GameController(World* model, sf::RenderWindow* window, Screen* joinGameScreen);
			~GameController();
			void handleInput(sf::Event &event);
			void setNetworkHandler(NetworkHandler* network);
            

        private:
			World* model;

			Player* currentPlayer;
			NetworkHandler* network;
    };
}

#endif
