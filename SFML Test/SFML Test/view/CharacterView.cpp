#include "CharacterView.h"

namespace mp
{
	// TODO: Remove last parameter, and create sprite in constructor.
	CharacterView::CharacterView(Character* character, AnimatedSprite* sprite)
	{
		this->character = character;
		this->sprite = sprite;
		this->facedRightLastUpdate = character->isFacingRight();
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
		
		if (character->isWalking())
			sprite->playAnimation("walk");
		else
			sprite->playAnimation("idle");

		// kinda ugly solution, "to be continued.."
		if (character->isFacingRight() != facedRightLastUpdate)
			sprite->scale(-1, 1);
		facedRightLastUpdate = character->isFacingRight();
	}

	void CharacterView::updateAnimation(int elapsed) {
		this->sprite->update(elapsed);
	}

	CharacterView::~CharacterView()
	{
	}
}