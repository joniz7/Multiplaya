////////////////////////////////////////////////////////////
/// Class representing a sound made by the UI, as opposed
/// to a world sound.
////////////////////////////////////////////////////////////
#ifndef UISOUND_H_INCLUDED
#define UISOUND_H_INCLUDED

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

#include "sound.h"

namespace mp
{
    class UISound : Sound
    {
        public:
			UISound();
            ~UISound();
			void playSound();
        private:
    };
}

#endif
