////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "animatedsprite.h"

////////////////////////////////////////////////////////////
/// Uses a sprite sheet and animations to represent animated
/// objects.
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
	AnimatedSprite::AnimatedSprite(sf::Texture* spriteSheet, sf::Vector2i sheetDimensions)
    {
		spriteSize.x = spriteSheet->getWidth() / sheetDimensions.x;
		spriteSize.y = spriteSheet->getHeight()  / sheetDimensions.y;

		// Save sheet dimensions
		this->sheetDimensions = sheetDimensions;
		// Set texture
		setTexture(*spriteSheet);
		// Set sprite scale accordingly
		setScale(1/(float)sheetDimensions.x,1/(float)sheetDimensions.y);
		// Initialize variables
		frame = 0;
		frameCounter = 0;
		p_anm = NULL;
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    AnimatedSprite::~AnimatedSprite()
    {
		delete(p_anm);
    }

	////////////////////////////////////////////////////////////
	// Adds an animation to the animation map.
	////////////////////////////////////////////////////////////
	void AnimatedSprite::addAnimation(std::string animationName, int fps, std::vector<sf::Vector2i> sequence)
	{
		Animation temp;
		temp.fps = fps;
		temp.sequence = sequence;
		animationMap[animationName] = temp;
	}

	////////////////////////////////////////////////////////////
	// Plays specified animation.
	////////////////////////////////////////////////////////////
	void AnimatedSprite::playAnimation(std::string animationName)
	{
		// TODO: Check if animation exist before playing.
		if(p_anm == &animationMap[animationName])
			return;
		else
			p_anm = &animationMap[animationName];
	}

	////////////////////////////////////////////////////////////
	// Sets a specified frame.
	////////////////////////////////////////////////////////////
	void AnimatedSprite::setFrame(sf::Vector2i frame)
	{
		sf::IntRect frameRect(
			spriteSize.x * frame.x,
			spriteSize.y * frame.y,
			spriteSize.x,
			spriteSize.y );

		setTextureRect(frameRect);
	}

	////////////////////////////////////////////////////////////
	// Updates the animated sprite.
	////////////////////////////////////////////////////////////
	void AnimatedSprite::update(float elapsed)
	{
		// Add elapsed time to frame counter.
		frameCounter += elapsed;
		// Check if we should advance one frame.
		if(frameCounter > (float)(1/p_anm->fps) )
		{
			setFrame(p_anm->sequence.at(frame));
			
			// Increment frame index unless we just displayed the last frame (in which case we simply reset the frame index).
			if(frame >= p_anm->sequence.size())
				frame = 0;
			else
				frame++;

			// Set frame counter to "left over" time to preserve time consistency.
			frameCounter = (float)(1/p_anm->fps) - frameCounter;
		}
	}
}
