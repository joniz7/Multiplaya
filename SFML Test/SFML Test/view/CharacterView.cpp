#include "CharacterView.h"

namespace mp
{

	CharacterView::CharacterView(Character* character) {
		this->character = character;

		this->sprite = new CharacterSprite("resources/test/testsprite.png",8);
		sprite->idle();
		
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
		sprite->setPosition(position.x * 1 / 10.0f, position.y * 1 / 10.0f);
		
		// Check if we're walking or not.
		if (character->isWalking()) {
			sprite->walk();
		} else {
			sprite->idle();
		}

		// Check which way we're facing.
		if (character->isFacingLeft()) {
			sprite->faceRight();
		} else {
			sprite->faceLeft();
		}
		

		worldDataMutex.unlock();
	}

	void CharacterView::updateAnimation(float elapsed) {
		this->sprite->update(elapsed);
	}

	CharacterView::~CharacterView()
	{
	}
}