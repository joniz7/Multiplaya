////////////////////////////////////////////////////////////
/// World data class. Holds all data used by world class for 
/// easy access from view and network handler.
////////////////////////////////////////////////////////////
#ifndef WORLDDATA_H_INCLUDED
#define WORLDDATA_H_INCLUDED

// Other headers
#include <string>
#include <vector>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include "../sfml.h"

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../game.h"

namespace mp
{
    class WorldData
    {
        public:
			WorldData();
            ~WorldData();
			std::vector<Character>* getChrVec(){return &chrVec;};
			std::vector<Bullet>* getBltVec(){return &bltVec;};
		private:
			// Vector containing bullets
			std::vector<Bullet> bltVec;
			// Vector containing characters
			std::vector<Character> chrVec;
			
    };
}

#endif
