#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "defines.h"

#include "../game.h"

namespace mp {
	class Player
	{
		public:
			Player(Character* character);
			~Player();
			void update();
		private:
			Character* character;
			bool released;

	};
}

#endif