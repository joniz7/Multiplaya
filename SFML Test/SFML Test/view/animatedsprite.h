////////////////////////////////////////////////////////////
/// Uses a sprite sheet and animations to represent animated
/// objects.
////////////////////////////////////////////////////////////
#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED

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
    class AnimatedSprite : sf::Sprite
    {
        public:
			AnimatedSprite();
            ~AnimatedSprite();
        private:
			sf::Texture* spriteSheet;
			sf::Vector2i sheetDimensions;
			
    };
}

#endif
