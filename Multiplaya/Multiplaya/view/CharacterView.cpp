#include "CharacterView.h"

namespace mp
{

	CharacterView::CharacterView(Character* character) {
		this->character = character;

		sf::Texture* tex = new sf::Texture();

		tex = ResourceHandler::instance().getTexture("resources/test/testsprite.png");

		this->sprite = new AnimatedSprite(tex,sf::Vector2i(8,3));

		this->sprite->rotate(180);
		this->sprite->setPosition(0,0);
		this->sprite->scale(0.0016f, 0.0016f);

		facingLeft = false;

		// Add animations
		std::vector<sf::Vector3i> sequence;
		sequence.push_back(sf::Vector3i(1,1,0));
		sprite->addAnimation("idle", 9, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector3i(1,2,0));
		sprite->addAnimation("jump", 60, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector3i(2,2,0));
		sprite->addAnimation("wallslide", 60, true, sequence);
		sequence.clear();

		
		sequence.push_back(sf::Vector3i(2,1,0));
		sequence.push_back(sf::Vector3i(3,1,0));
		sequence.push_back(sf::Vector3i(4,1,0));
		sequence.push_back(sf::Vector3i(5,1,0));
		sequence.push_back(sf::Vector3i(6,1,0));
		sequence.push_back(sf::Vector3i(7,1,0));
		sprite->addAnimation("walk", 9, true, sequence);
		
		/*
		sequence.push_back(sf::Vector3i(1,2,0));
		sequence.push_back(sf::Vector3i(2,2,0));
		sequence.push_back(sf::Vector3i(3,2,0));
		sequence.push_back(sf::Vector3i(4,2,0));
		sequence.push_back(sf::Vector3i(5,2,0));
		sequence.push_back(sf::Vector3i(6,2,0));
		sequence.push_back(sf::Vector3i(7,2,0));
		sequence.push_back(sf::Vector3i(8,2,0));
		*/


		sequence.clear();

		sequence.push_back(sf::Vector3i(3,2,40));
		sequence.push_back(sf::Vector3i(3,2,80));
		sequence.push_back(sf::Vector3i(3,2,120));
		sequence.push_back(sf::Vector3i(3,2,160));
		sequence.push_back(sf::Vector3i(3,2,200));
		sequence.push_back(sf::Vector3i(3,2,240));
		sequence.push_back(sf::Vector3i(3,2,260));
		sequence.push_back(sf::Vector3i(3,2,320));
		sequence.push_back(sf::Vector3i(3,2,360));


		sequence.push_back(sf::Vector3i(1,2,0));
		sprite->addAnimation("airroll", 40, false, sequence);
		sequence.clear();

		sprite->playAnimation("idle");
		
	}

	void CharacterView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*sprite, states);
	}

	void CharacterView::updatePosition()
	{
		worldDataMutex.lock();

		b2Vec2 position = character->getBody()->GetPosition();
		float32 angle = character->getBody()->GetAngle();
		
		//todo define pixelscale globaly
		sprite->setPosition(position.x * PIXEL_SCALE, position.y * PIXEL_SCALE);
		
		// Check what animation to play.
		if( character->isWallSliding() )
			sprite->playAnimation("wallslide");
		else if (!character->isGrounded())
		{
			if(character->isFlipping())
				sprite->playAnimation("airroll");
			else
				sprite->playAnimation("jump");
		}
		else if (character->isWalking())
			sprite->playAnimation("walk");
		else
			sprite->playAnimation("idle");

		// Check which way we're facing.
		if(character->isFacingLeft() != facingLeft)
		{
			sprite->scale(-1,1);
			facingLeft = character->isFacingLeft();
		}
		
		worldDataMutex.unlock();
	}

	void CharacterView::updateAnimation(float elapsed) {
		this->sprite->update(elapsed);
	}

	CharacterView::~CharacterView()
	{
		delete sprite;
	}
}