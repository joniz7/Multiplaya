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

namespace mp
{
	//Forward declaration so World can have a WorldData pointer
	class World;

    class Controller
    {
        public:
			Controller(World* model, WorldView* view, NetworkHandler* network);
			~Controller();
			void exec();
            

        private:
			World* model;
			WorldView* view;
			Player* currentPlayer;
			NetworkHandler* network;
    };
}

#endif
