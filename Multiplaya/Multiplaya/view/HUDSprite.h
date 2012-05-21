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
#include "animatedsprite.h"
#include "../services/resourcehandler.h"

namespace mp
{
    class HUDSprite : public sf::Drawable
    {
        public:
			HUDSprite(std::string path, sf::Vector2i dimensions);
            ~HUDSprite();
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			int getWidth()  {return (int)sprite->getSize().x; }
			int getHeight() {return (int)sprite->getSize().y; }
			void setPosition(float x, float y) { sprite->setPosition(x,y); };
			void update(float elapsed);
			void setState(int i);	// Change state.
			void setFrame(sf::Vector3i frame) { sprite->setFrame(frame); };	// Sets a specified frame.
        private:
			AnimatedSprite* sprite;
			sf::Texture* spriteSheet; // The texture containing all frames.
			std::map<int, sf::Vector3i> states;	// Keeps track of all our states.
			int state;  // Current state.
			int numberOfStates; // Total amount of states.	
    };
}

#endif
