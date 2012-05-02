#include "CharacterView.h"

namespace mp
{
	//CharacterView::CharacterView(Character* character, sf::Sprite* sprite)
	CharacterView::CharacterView(Character* character, AnimatedSprite* sprite)
	{
		this->character = character;
		this->sprite = sprite;
		this->facedRightLastUpdate = false;
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

		if (character->isFacingRight() != facedRightLastUpdate)
			sprite->scale(-1, 1);
		facedRightLastUpdate = character->isFacingRight();
	}

	CharacterView::~CharacterView()
	{
	}
}