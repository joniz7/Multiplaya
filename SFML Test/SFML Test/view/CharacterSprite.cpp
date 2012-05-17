////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "CharacterSprite.h"

////////////////////////////////////////////////////////////
/// Uses a sprite sheet and animations to represent animated
/// objects.
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	/// Creates a new character sprite from the supplied path.
	///
	/// \param  path - the path to the sprite image. We assume that
	///			the first frame is the idle animation.
	/// \param frames - the number of frames in the animation.
	////////////////////////////////////////////////////////////
	CharacterSprite::CharacterSprite(std::string path, int frames) : sf::Sprite() {
		
		// Fetch our texture from the supplied path.
		spriteSheet = new sf::Texture();
		if (!spriteSheet->loadFromFile(path)) {
			std::cout << "CharacterSprite: resource loading failed: " << path << std::endl;
		}
		// Set our texture.
		setTexture(*spriteSheet);

		// ----- Specify our animations. -----
		// First frame is assumed to be the idle image.
		std::vector<int> sequence;
		sequence.push_back(1);
		this->addAnimation("idle", 9, true, sequence);
		sequence.clear();
		
		// All others are our walking frames.
		for(int i=2;i<frames;i++) {
			sequence.push_back(i);
			std::cout << "pushing "<<i<<". Should go to 7."<<std::endl;
		} this->addAnimation("walk", 9, true, sequence);
		sequence.clear();
		// -----------------------------------

		this->rotate(180);
		this->setPosition(0,0);
		this->scale(0.0016f, 0.0016f);

		//setTextureRect(sf::IntRect(0,0,spriteSheet->getSize().x/frames,spriteSheet->getSize().y));
		
		// Calculate sprite size
		spriteSize.x = spriteSheet->getSize().x / frames;
		spriteSize.y = spriteSheet->getSize().y;
		// Center origins
		setOrigin(spriteSize.x/2,spriteSize.y/2);;
		// Initialize variables
		frame = 0;
		frameCounter = 0;
		p_anm = NULL;
		setFrame(0);
    }

	////////////////////////////////////////////////////////////
	/// Plays the walking animation of the character sprite.
	////////////////////////////////////////////////////////////
	void CharacterSprite::walk() {
		this->playAnimation("walk");
	}
	////////////////////////////////////////////////////////////
	/// Plays the idle animation of the character sprite.
	////////////////////////////////////////////////////////////
	void CharacterSprite::idle() {
		this->playAnimation("idle");
	}
	////////////////////////////////////////////////////////////
	/// Turns the character in the opposite direction.
	////////////////////////////////////////////////////////////
	void CharacterSprite::turnAround() {
		this->scale(-1, 1);
		facingLeft = !facingLeft;
	}
	////////////////////////////////////////////////////////////
	/// Turns the character to the left.
	////////////////////////////////////////////////////////////
	void CharacterSprite::faceLeft() {
		if (facingLeft) {
			return;
		} else {
			this->turnAround();
		}
	}
	////////////////////////////////////////////////////////////
	/// Turns the character to the right.
	////////////////////////////////////////////////////////////
	void CharacterSprite::faceRight() {
		if (!facingLeft) {
			return;
		} else {
			this->turnAround();
		}		
	}

	////////////////////////////////////////////////////////////
	// Adds an animation to the animation map.
	////////////////////////////////////////////////////////////
	void CharacterSprite::addAnimation(const std::string & animationName, int fps, bool loop, std::vector<int> sequence)
	{
		CharacterAnimation temp;
		temp.fps = fps;
		temp.loop = loop;
		temp.sequence = sequence;
		animationMap[animationName] = temp;
		p_anm = &animationMap[animationName];
	}

	////////////////////////////////////////////////////////////
	// Plays specified animation.
	////////////////////////////////////////////////////////////
	void CharacterSprite::playAnimation(const std::string & animationName)
	{
		// TODO: Check if animation exist before playing.
		if(p_anm == &animationMap[animationName]) {
			return;
		}
		else {
			// std::cout<<"New animation playing: "<<animationName<<std::endl;
			p_anm = &animationMap[animationName];
			frame = 0;
			frameCounter = 0;
		}
	}

	////////////////////////////////////////////////////////////
	// Sets a specified frame.
	////////////////////////////////////////////////////////////
	void CharacterSprite::setFrame(int frame)
	{
		sf::IntRect frameRect(
			spriteSize.x * (frame-1),
			0,
			spriteSize.x,
			spriteSize.y
			);

		setTextureRect(frameRect);
	}

	////////////////////////////////////////////////////////////
	// Updates the animated sprite.
	////////////////////////////////////////////////////////////
	void CharacterSprite::update(float elapsed) {
		// Add elapsed time to frame counter.
		frameCounter += elapsed;
		// Check if we should advance one frame.
		if(frameCounter > (1/p_anm->fps) ) {
			setFrame(p_anm->sequence.at(frame));
			
			// Increment frame index unless we just displayed the last frame (in which case we simply reset the frame index if we are looping).
			if(frame >= p_anm->sequence.size()-1)
				if(p_anm->loop) {
					frame = 0;
				} else {
					return;
				}
			else {
				frame++;
			}

			// Set frame counter to "left over" time to preserve time consistency.
			frameCounter = (float)(1/p_anm->fps) - frameCounter;
		}
	}
	

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    CharacterSprite::~CharacterSprite() {
		delete p_anm;
		delete spriteSheet;
    }
}
