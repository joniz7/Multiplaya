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
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../game.h"

namespace mp
{
    class World
    {
        public:
			World( );
            ~World();
        private:
			
    };
}

#endif
