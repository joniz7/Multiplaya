#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "defines.h"

#include "../game.h"

#include "worlddata.h"

namespace mp {

	class Player
	{
		public:
			Player(WorldData* worldData, b2World* world);
			~Player();
			void update();
			void setCharacter(Character* character);
			Character* getCharacter() { return character; }
		private:
			Character* character;
			bool released;
			WorldData* worldData;
			b2World* world;
	};
}

#endif