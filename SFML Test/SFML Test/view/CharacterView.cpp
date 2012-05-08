#include "CharacterView.h"

namespace mp
{
	CharacterView::CharacterView(Character* character)
	{
		this->character = character;
		this->facedRightLastUpdate = character->isFacingRight();

		createAnimatedSprite();
	}

	void CharacterView::createAnimatedSprite() {
		frameTexture = new sf::Texture();
		frameTexture->loadFromFile("resources/test/testsprite.png");
		
		sprite = new AnimatedSprite(frameTexture,sf::Vector2i(8, 1));

		// Walking animation
		std::vector<sf::Vector2i> sequence;
		sequence.push_back(sf::Vector2i(2, 1));
		sequence.push_back(sf::Vector2i(3, 1));
		sequence.push_back(sf::Vector2i(4, 1));
		sequence.push_back(sf::Vector2i(5, 1));
		sequence.push_back(sf::Vector2i(6, 1));
		sequence.push_back(sf::Vector2i(7, 1));
		sprite->addAnimation("walk", 9, true, sequence);
		sequence.clear();
		// Idle animation
		sequence.push_back(sf::Vector2i(1, 1));
		sprite->addAnimation("idle", 9, true, sequence);

		sprite->rotate(180);
		sprite->setPosition(0,0);
		sprite->scale(0.0016f, 0.0016f);
		sprite->playAnimation("idle");
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
		
		if (character->isWalking()) {
			sprite->playAnimation("walk");
		}
		else {
			sprite->playAnimation("idle");
		}

		// kinda ugly solution, "to be continued.."
		if (character->isFacingRight() != facedRightLastUpdate)
			sprite->scale(-1, 1);
		facedRightLastUpdate = character->isFacingRight();
	}

	void CharacterView::updateSprite(int elapsed) {
		this->sprite->update(elapsed);
	}

	CharacterView::~CharacterView()
	{
		// Delete dynamically created object. Oh, java garbage collection, I miss you.
		delete sprite;
		delete frameTexture;
	}
}