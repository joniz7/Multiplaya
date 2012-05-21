////////////////////////////////////////////////////////////
/// Class description
////////////////////////////////////////////////////////////
#ifndef SOUNDHANDLER_H_INCLUDED
#define SOUNDHANDLER_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include "sfml.h"

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "defines.h"

namespace mp
{
    class SoundHandler
    {
        public:
			SoundHandler();
            ~SoundHandler();
			void playSound( std::string filePath );
        private:
			
    };
}

#endif
