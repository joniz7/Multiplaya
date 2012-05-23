#include "CharacterView.h"

namespace mp
{
	/**
	 * Create a new CharacterView, tied to the supplied ICharacter.
	 * 
	 * @param character - the ICharacter we're representing.
	 */
	CharacterView::CharacterView(ICharacter* character) {
		this->character = character;

		sf::Texture* tex = new sf::Texture();

		tex = ResourceHandler::instance().getTexture("resources/test/testsprite.png");

		this->sprite = new AnimatedSprite(tex,sf::Vector2i(9,3));

		this->sprite->rotate(180);
		this->sprite->setPosition(0,0);
		this->sprite->scale(0.0016f, 0.0016f);

		facingLeft = false;

		// Add animations
		std::vector<sf::Vector3i> sequence;
		sequence.push_back(sf::Vector3i(4,3,0));
		sprite->addAnimation("idle", 9, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector3i(1,3,0));
		sprite->addAnimation("jump", 60, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector3i(2,3,0));
		sprite->addAnimation("wallslide", 60, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector3i(1,1,0));
		sequence.push_back(sf::Vector3i(2,1,0));
		sequence.push_back(sf::Vector3i(3,1,0));
		sequence.push_back(sf::Vector3i(4,1,0));
		sequence.push_back(sf::Vector3i(5,1,0));
		sequence.push_back(sf::Vector3i(6,1,0));
		sequence.push_back(sf::Vector3i(7,1,0));
		sequence.push_back(sf::Vector3i(8,1,0));
		sequence.push_back(sf::Vector3i(9,1,0));

		sprite->addAnimation("walk", 16, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector3i(9,1,0));
		sequence.push_back(sf::Vector3i(8,1,0));
		sequence.push_back(sf::Vector3i(7,1,0));
		sequence.push_back(sf::Vector3i(6,1,0));
		sequence.push_back(sf::Vector3i(5,1,0));
		sequence.push_back(sf::Vector3i(4,1,0));
		sequence.push_back(sf::Vector3i(3,1,0));
		sequence.push_back(sf::Vector3i(2,1,0));
		sequence.push_back(sf::Vector3i(1,1,0));

		sprite->addAnimation("walkbackwards", 16, true, sequence);
		sequence.clear();
		
		sequence.push_back(sf::Vector3i(1,2,0));
		sequence.push_back(sf::Vector3i(2,2,0));
		sequence.push_back(sf::Vector3i(3,2,0));
		sequence.push_back(sf::Vector3i(4,2,0));
		sequence.push_back(sf::Vector3i(5,2,0));
		sequence.push_back(sf::Vector3i(6,2,0));
		sequence.push_back(sf::Vector3i(7,2,0));
		sequence.push_back(sf::Vector3i(8,2,0));

		sprite->addAnimation("run", 16, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector3i(3,3,40));
		sequence.push_back(sf::Vector3i(3,3,80));
		sequence.push_back(sf::Vector3i(3,3,120));
		sequence.push_back(sf::Vector3i(3,3,160));
		sequence.push_back(sf::Vector3i(3,3,200));
		sequence.push_back(sf::Vector3i(3,3,240));
		sequence.push_back(sf::Vector3i(3,3,260));
		sequence.push_back(sf::Vector3i(3,3,320));
		sequence.push_back(sf::Vector3i(3,3,360));

		sequence.push_back(sf::Vector3i(1,3,0));
		sprite->addAnimation("airroll", 40, false, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector3i(3,3,-40));
		sequence.push_back(sf::Vector3i(3,3,-80));
		sequence.push_back(sf::Vector3i(3,3,-120));
		sequence.push_back(sf::Vector3i(3,3,-160));
		sequence.push_back(sf::Vector3i(3,3,-200));
		sequence.push_back(sf::Vector3i(3,3,-240));
		sequence.push_back(sf::Vector3i(3,3,-260));
		sequence.push_back(sf::Vector3i(3,3,-320));
		sequence.push_back(sf::Vector3i(3,3,-360));

		sequence.push_back(sf::Vector3i(1,3,0));
		sprite->addAnimation("airroll2", 40, false, sequence);
		sequence.clear();

		sprite->playAnimation("idle");
		
	}

	void CharacterView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*sprite, states);
	}

	/**
	 * Updates the position of this CharacterView.
	 * 
	 * Fetches the position and state from our ICharacter, and
	 * chooses an animation depending on the state (jumping, walking etc).
	 */
	void CharacterView::update()
	{
		updateAnimation( (float) (1.0f / 60.0f) );
	
		b2Vec2 position = character->getBody()->GetPosition();
		//float32 angle = character->getBody()->GetAngle();
		sprite->setPosition(position.x * PIXEL_SCALE, position.y * PIXEL_SCALE);
		
		// Check what animation to play.
		if( character->isWallSliding() )
			sprite->playAnimation("wallslide");
		else if (!character->isGrounded())
		{
			if(character->isFlipping())
			{
				if(character->isFacingLeft())
					sprite->playAnimation("airroll2");
				else
					sprite->playAnimation("airroll");
			}
			else
				sprite->playAnimation("jump");
		}
		else if (character->isWalking())
		{
			if(character->isFocusing())
			{
				if(!character->isBackwards())
					sprite->playAnimation("walk");
				else
					sprite->playAnimation("walkbackwards");
			}
			else
				sprite->playAnimation("run");
		}
		else
			sprite->playAnimation("idle");

		// Check which way we're facing.
		if(character->isFacingLeft() != facingLeft)
		{
			sprite->scale(-1,1);
			facingLeft = character->isFacingLeft();
		}
	}

	/**
	 * Updates the sprite.
	 */
	void CharacterView::updateAnimation(float elapsed) {
		this->sprite->update(elapsed);
	}

	/**
	 * Destructor. Deletes the sprite.
	 */
	CharacterView::~CharacterView()
	{
		delete sprite;
	}
}