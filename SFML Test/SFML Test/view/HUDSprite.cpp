////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "HUDSprite.h"

////////////////////////////////////////////////////////////
/// Uses a sprite sheet to represent different states of the HUD.
/// Allows switching of states easily, via method setState().
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
	HUDSprite::HUDSprite(std::string path, int states) : sf::Sprite() {
		
		// Load texture.
		spriteSheet = new sf::Texture();
		if ( !spriteSheet->loadFromFile(path) ) {
			std::cout << "Failed to load texture: "<< path << std::endl;
		}
		
		// Set texture.
		setTexture(*spriteSheet);

		// Calculate the size of a frame.
		spriteSize.x = spriteSheet->getSize().x / states;
		spriteSize.y = spriteSheet->getSize().y;

		// Save total number of states.
		this->states = states;
		
		// We start at state 0.
		setState(0);
    }

	////////////////////////////////////////////////////////////
	/// Sets a specified frame.
	/// \param state - Minimum value 0.
	////////////////////////////////////////////////////////////
	void HUDSprite::setState(int state)
	{	// Inputted state is the current one.
		if (this->state == state) {
			return;
		}// Input too big.
		else if (state > states) {
			this->setState(states); return;
		}// Input too small.
		else if (state < 0) {
			this->setState(0); return;
		}// Input is all good!
		else {
			// Set state.
			this->state = state;
			// Create box around our chosen frame.
			sf::IntRect frameRect(
				spriteSize.x * (state),
				0,
				spriteSize.x,
				spriteSize.y
			);
			// Apply our frame change.
			setTextureRect(frameRect);
		}
	}


	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    HUDSprite::~HUDSprite() {
		delete spriteSheet;
	}

}
