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
	AnimatedSprite::AnimatedSprite(sf::Texture* spriteSheet, sf::Vector2i sheetDimensions) : sf::Sprite(*spriteSheet,sf::IntRect(0,0,spriteSheet->getSize().x/sheetDimensions.x,spriteSheet->getSize().y / sheetDimensions.y))
    {
		// Calculate sprite size
		spriteSize.x = float(spriteSheet->getSize().x) / float(sheetDimensions.x);
		spriteSize.y = float(spriteSheet->getSize().y) / float(sheetDimensions.y);
		// Center origins
		setOrigin(spriteSize.x/2,spriteSize.y/2);
		// Save sheet dimensions
		this->sheetDimensions = sheetDimensions;
		// Initialize variables
		frame = 0;
		frameCounter = 0;
		p_anm = NULL;
		setFrame(sf::Vector3i(0,0,0));
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
	void AnimatedSprite::addAnimation(const std::string & animationName, int fps, bool loop, std::vector<sf::Vector3i> sequence)
	{
		Animation temp;
		temp.fps = float(fps);
		temp.loop = loop;
		temp.sequence = sequence;
		animationMap[animationName] = temp;
		p_anm = &animationMap[animationName];
	}

	////////////////////////////////////////////////////////////
	// Plays specified animation.
	////////////////////////////////////////////////////////////
	void AnimatedSprite::playAnimation(const std::string & animationName)
	{
		// TODO: Check if animation exist before playing.
		if(p_anm == &animationMap[animationName])
			return;
		else
		{
			// std::cout<<"New animation playing: "<<animationName<<std::endl;
			p_anm = &animationMap[animationName];
			frame = 0;
			frameCounter = 0;
		}
	}

	////////////////////////////////////////////////////////////
	// Sets a specified frame.
	////////////////////////////////////////////////////////////
	void AnimatedSprite::setFrame(sf::Vector3i frame)
	{
		sf::IntRect frameRect(
			int(spriteSize.x * (frame.x-1)),
			int(spriteSize.y * (frame.y-1)),
			int(spriteSize.x),
			int(spriteSize.y)
			);

		setTextureRect(frameRect);
		setRotation(frame.z+180);
	}

	////////////////////////////////////////////////////////////
	// Updates the animated sprite.
	////////////////////////////////////////////////////////////
	void AnimatedSprite::update(float elapsed)
	{
		// Add elapsed time to frame counter.
		frameCounter += elapsed;
		// Check if we should advance one frame.
		if(frameCounter > (1/p_anm->fps) )
		{
			//std::cout<<"Frame advance "<<(1/(p_anm->fps))<<std::endl;
			
			setFrame(p_anm->sequence.at(frame));
			
			// Increment frame index unless we just displayed the last frame (in which case we simply reset the frame index if we are looping).
			if(frame >= p_anm->sequence.size()-1)
				if(p_anm->loop)
					frame = 0;
				else
					return;
			else
				frame++;

			// Set frame counter to "left over" time to preserve time consistency.
			frameCounter = (float)(1/p_anm->fps) - frameCounter;
			
		}
	}
}
