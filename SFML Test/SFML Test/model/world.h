////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////
#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

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

namespace mp
{
	//Forward declaration so World can have a WorldData pointer
	class WorldData;

    class World
    {
        public:
			World(WorldData* worldData);
			void exec();
            ~World();
			b2World* getWorld(){return world;};
			WorldData* getWorldData();
        private:
			WorldData* worldData;
			b2World* world;
    };
}

#endif
