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
