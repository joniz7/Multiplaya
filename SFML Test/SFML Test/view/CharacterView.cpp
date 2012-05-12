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

	CharacterView::CharacterView(Character* character) {
		this->character = character;
		this->facedRightLastUpdate = character->isFacingRight();

		// ---- Character's Sprite ----
		texture = new sf::Texture();
		texture->loadFromFile("resources/test/testsprite.png");

		sprite = new AnimatedSprite(texture,sf::Vector2i(8, 1));
		std::vector<sf::Vector2i> sequence;
		sequence.push_back(sf::Vector2i(2, 1));
		sequence.push_back(sf::Vector2i(3, 1));
		sequence.push_back(sf::Vector2i(4, 1));
		sequence.push_back(sf::Vector2i(5, 1));
		sequence.push_back(sf::Vector2i(6, 1));
		sequence.push_back(sf::Vector2i(7, 1));
		sprite->addAnimation("walk", 9, true, sequence);
		sequence.clear();
		
		sequence.push_back(sf::Vector2i(1, 1));
		sprite->addAnimation("idle", 9, true, sequence);
		sequence.clear();

		sprite->rotate(180);
		sprite->setPosition(0,0);
		sprite->scale(0.0016f, 0.0016f);
		sprite->playAnimation("idle");
		// ----------------------------
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
		if (character->isFacingRight() != facedRightLastUpdate) {
			std::cout << "character facing right? " << character->isFacingRight() << std::endl;
			sprite->scale(-1, 1);
		}
		facedRightLastUpdate = character->isFacingRight();
	}

	void CharacterView::updateAnimation(int elapsed) {
		this->sprite->update(elapsed);
	}

	CharacterView::~CharacterView()
	{
	}
}