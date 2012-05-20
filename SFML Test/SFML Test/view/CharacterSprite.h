////////////////////////////////////////////////////////////
/// Uses a sprite sheet and animations to represent animated
/// objects.
////////////////////////////////////////////////////////////
#ifndef CHARACTERSPRITE_H_INCLUDED
#define CHARACTERSPRITE_H_INCLUDED

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
	struct CharacterAnimation{
		// Playback fps.
		float fps;
		// Should this CharacterAnimation loop?
		bool loop;
		// Sequence vector containing the frames in playback order.
		std::vector<int> sequence;
	};

    class CharacterSprite : public sf::Sprite
    {
        public:
			CharacterSprite(std::string path, int frames);
            ~CharacterSprite();
			void walk();
			void idle();
			void turnAround();
			void faceLeft();
			void faceRight();
			void update(float elapsed);	// Updates the animated sprite.

		private:
			void setFrame(int frame);	// Sets a specified frame.
			void addAnimation(const std::string & animationName, int fps, bool loop, std::vector<int> sequence);	// Adds an animation to the animation map.
			void playAnimation(const std::string & animationName);	// Plays specified animation.

			bool facingLeft;
			std::map<std::string, CharacterAnimation> animationMap;	// Map containing all animations for the animated sprite.
			sf::Texture* spriteSheet;	// Pointer to sprite sheet.
			float frameCounter;		// Keeps track of when to frame advance.
			unsigned int frame;	// Keeps track of which frame of an animation currently is being shown
			CharacterAnimation* p_anm;	// Pointer to animation currently playing.
			sf::Vector2f spriteSize; // The size of each frame.
    };
}

#endif
