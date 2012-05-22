////////////////////////////////////////////////////////////
/// Uses a sprite sheet to represent different states of the HUD.
/// Allows switching of states easily, via method setState().
////////////////////////////////////////////////////////////
#ifndef HUDSPRITE_H_INCLUDED
#define HUDSPRITE_H_INCLUDED

// Other headers
#include <string>
#include <iostream>
#include <cstdlib>
#include <list>
#include <cmath>
#include <map>

// SFML specific headers
#include "../sfml.h"

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "../defines.h"

namespace mp
{
    class HUDSprite : public sf::Sprite
    {
        public:
			HUDSprite(std::string path, int states);
            ~HUDSprite();
			int getWidth() {return (int)spriteSize.x;}
			int getHeight() {return (int)spriteSize.y;}
			void setState(int i);	// Change state.
        private:
			sf::Texture* spriteSheet; // The texture containing all frames.
			sf::Vector2i spriteSize; // The size of each frame.
			int state;	// Keeps track of which state is currently active.
			int states; // Total amount of states.	
    };
}

#endif
