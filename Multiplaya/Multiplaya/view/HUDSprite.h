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
#include <SFML/Graphics.hpp>

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "../services/resourcehandler.h"

namespace mp
{
	/**
	* Uses a sprite sheet to represent different states of the HUD.
	* Allows switching of states easily, via method setState().
	*/
	class HUDSprite : public sf::Sprite
    {
        public:
			HUDSprite(std::string path, sf::Vector2i dimensions);
            ~HUDSprite();
			int getWidth() {return (int)spriteSize.x;}
			int getHeight() {return (int)spriteSize.y;}
			void setState(int i);
        private:
			sf::Texture* spriteSheet; ///< The texture containing all frames.
			sf::Vector2i spriteSize; ///< The size of each frame.
			
			int state;	///< Keeps track of which state is currently active.
			std::map<int, sf::Vector2i> states; ///< Keeps track of all states.
			int numberOfStates; ///< Total amount of states.	
    };
}

#endif
