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
	HUDSprite::HUDSprite(std::string path, sf::Vector2i dimensions) {
		
		numberOfStates = 0;

		// Load texture.
		spriteSheet = new sf::Texture();
		spriteSheet = ResourceHandler::instance().getTexture(path);

		sprite = new AnimatedSprite(spriteSheet, dimensions);
		sprite->rotate(180);
		sprite->setPosition(0,0);

		// Add animation.
		std::vector<sf::Vector3i> sequence;
		sequence.push_back(sf::Vector3i(1,1,0));
		sprite->addAnimation("ammo", 9, true, sequence);
		sequence.clear();

		// Populate our 'states' map.
		for (int i=1;i<=dimensions.x;i++) {
			for (int j=1;j<=dimensions.y;j++) {
				std::cout << "hej! ("<< j << "," << i <<",0)"<< std::endl;
				states[0] = sf::Vector3i(j,i,0);
				numberOfStates++;
			}
		}
		std::cout << "numberOfStates: "<<numberOfStates << "." << std::endl;
		
		// We start at state 0.
		//sprite->setFrame( sf::Vector3i(1,1,0) );
    }

	void HUDSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*sprite, states);
		//window.draw( sf::RectangleShape(sf::Vector2f(300,300)) );
		//std::cout <<"HUDSprite: x: "<<sprite->getPosition().x << "y:"<<sprite->getPosition().y<<std::endl;
	}

	////////////////////////////////////////////////////////////
	/// Sets a specified frame.
	/// \param state - Minimum value 0.
	////////////////////////////////////////////////////////////
	void HUDSprite::setState(int state)
	{	
		// If it's the same, do nothing.
		if (this->state == state) {}

		// Input too big, set to max.
		else if (state > numberOfStates) {
			std::cout << "setState("<<state<<"). Too big!"<<std::endl;
			sprite->setFrame(states[numberOfStates]);
			this->state = numberOfStates;
		}
		// Input too small, set to min.
		else if (state < 0) {
			std::cout << "setState("<<state<<"). Too small!"<<std::endl;
			sprite->setFrame(states[0]);
			this->state = 0;
		}
		// Input is all good!
		else {
			std::cout << "setState("<<state<<"). Just enough."<<std::endl;
			// Set state.
			this->state = state;
			// Set correct frame.
			sprite->setFrame(states[state]);
		}
	}

	void HUDSprite::update(float elapsed) {
		this->sprite->update(elapsed);
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    HUDSprite::~HUDSprite() {
		//delete spriteSheet;
	}

}
