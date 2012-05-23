// Class header
#include "HUDSprite.h"

namespace mp {

	/**
	 * Creates a new HUDSprite.
	 * 
	 * @param path - the path to the image of the sprite.
	 * @param dimensions - the dimensions of the sprite sheet.
	 */
	HUDSprite::HUDSprite(std::string path, sf::Vector2i dimensions)		   
		: sf::Sprite() {
		
		// Load texture from path.
		spriteSheet = ResourceHandler::instance().getTexture(path);
		this->setTexture(*spriteSheet);

		// Calculate the size of a frame.
		spriteSize.x = spriteSheet->getSize().x / dimensions.x;
		spriteSize.y = spriteSheet->getSize().y / dimensions.y;

		numberOfStates = 0;
		// Assign to each state a position on the texture.
		for (int i=1;i<=dimensions.y;i++) {
			for (int j=1;j<=dimensions.x;j++) {
				states[numberOfStates++] = sf::Vector2i(j,i);
			}
		}
		
		// We start at state 0.
		setState(0);
    }

	/**
	 * Sets a specified frame.
	 * @param state minimum value 0.
	 */
	void HUDSprite::setState(int state)
	{	
		// Inputted state is the current one.
		if (this->state == state) {
			return;
		}
		// Input too big.
		else if (state > numberOfStates) {
			this->setState(numberOfStates); return;
		}
		// Input too small.
		else if (state < 0) {
			this->setState(0); return;
		}
		// Input is all good!
		else {
			this->state = state;
			// Create box around our chosen frame.
			sf::IntRect frameRect(
				spriteSize.x * (states[state].x-1),
				spriteSize.y * (states[state].y-1),
				spriteSize.x,
				spriteSize.y
			);
			// Apply our frame change.
			setTextureRect(frameRect);
		}
	}

    HUDSprite::~HUDSprite() {
		delete spriteSheet;
	}

}
