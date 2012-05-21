////////////////////////////////////////////////////////////
/// Class representing a sound in the world, as opposed to
/// a UI sound.
////////////////////////////////////////////////////////////
#ifndef WORLDSOUND_H_INCLUDED
#define WORLDSOUND_H_INCLUDED

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
    class WorldSound : Sound
    {
        public:
			WorldSound(float x, float y);
            ~WorldSound();
			void playSound();
        private:
			float decay;		// Determines how sound level drops over distance. Higher value means higher loss of volume.
			float sharpness;	// Determines sound penetration. Higher value means less muffling when sound is heard through walls.
			b2Vec2 position;	// Origin of sound in world coordinates.
    };
}

#endif
