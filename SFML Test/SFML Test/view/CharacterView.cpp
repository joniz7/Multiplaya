#include "CharacterView.h"

namespace mp
{
	// TODO: Remove last parameter, and create sprite in constructor.
	CharacterView::CharacterView(Character* character, CharacterSprite* sprite) {
		this->character = character;
		this->sprite = sprite;
	}

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

	}

	void CharacterView::updateAnimation(float elapsed) {
		this->sprite->update(elapsed);
	}

	CharacterView::~CharacterView()
	{
	}
}