////////////////////////////////////////////////////////////
/// Abstract sound class
////////////////////////////////////////////////////////////
#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include "../sfml.h"

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "../defines.h"

namespace mp
{
    class Sound
    {
        public:
			Sound();
            ~Sound();
			virtual void playSound() = 0;
        private:
			float volume;
			
    };
}

#endif
