////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "worldsound.h"

////////////////////////////////////////////////////////////
/// Class representing a sound in the world, as opposed to
/// a UI sound.
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    WorldSound::WorldSound(float x, float y)
    {
		position = b2Vec2(x,y);
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    WorldSound::~WorldSound()
    {

    }

	void WorldSound::playSound()
	{
		// Reverb: Cast x amount of rays around sound position to determine room size. Add reverb as needed.
		// Volume: Measure distance to camera focus coordinates. Determine sound level by using (max volume)-(distance)*(decay).
		// Muffling: Cast a ray to camera focus coordinates. Muffle the sound by using (world intersections)/(sharpness).
		// Play the sound.
	}
}