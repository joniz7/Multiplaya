////////////////////////////////////////////////////////////
/// World data class. Holds all data world class uses for 
/// easy access from view and network handler
////////////////////////////////////////////////////////////
#ifndef WORLDDATA_H_INCLUDED
#define WORLDDATA_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
        private:
			
    };
}

#endif
