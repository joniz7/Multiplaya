////////////////////////////////////////////////////////////
/// Uses a sprite sheet and animations to represent animated
/// objects.
////////////////////////////////////////////////////////////
#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED

// Other headers
#include <string>
#include <iostream>
#include <cstdlib>
#include <list>
#include <cmath>
#include <map>

// SFML specific headers
#include "../sfml.h"

//Defines
#include "../defines.h"

namespace mp
{
	struct Animation{
		// Playback fps.
		float fps;
		// Should this animation loop?
		bool loop;
		// Sequence vector containing the frames in playback order.
		std::vector<sf::Vector3i> sequence;
	};

    class AnimatedSprite : public sf::Sprite
    {
        public:
			AnimatedSprite(sf::Texture* spriteSheet, sf::Vector2i sheetDimensions);
            ~AnimatedSprite();
			void addAnimation(const std::string & animationName, int fps, bool loop, std::vector<sf::Vector3i> sequence);	// Adds an animation to the animation map.
			void playAnimation(const std::string & animationName);	// Plays specified animation.
			void setFrame(sf::Vector3i frame);	// Sets a specified frame.
			void update(float elapsed);	// Updates the animated sprite.
        private:
			std::map<std::string, Animation> animationMap;	// Map containing all animations for the animated sprite.
			sf::Texture* spriteSheet;	// Pointer to sprite sheet.
			sf::Vector2i sheetDimensions;	// The amount of frames in height and width present in the sprite sheet.
			float frameCounter;		// Keeps track of when to frame advance.
			int frame;	// Keeps track of which frame of an animation currently is being shown
			Animation* p_anm;	// Pointer to animation currently playing.
			sf::Vector2f spriteSize;
			
    };
}

#endif
