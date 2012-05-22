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
#include <SFML/Audio.hpp>
#include "../defines.h"

// Box2D specific headers
#include <Box2D.h>

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
