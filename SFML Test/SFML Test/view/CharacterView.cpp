#include "CharacterView.h"

namespace mp
{

	CharacterView::CharacterView(Character* character) {
		this->character = character;

		sf::Texture* tex = new sf::Texture();
		tex->loadFromFile("resources/test/testsprite.png");

		this->sprite = new AnimatedSprite(tex,sf::Vector2i(8,2));

		this->sprite->rotate(180);
		this->sprite->setPosition(0,0);
		this->sprite->scale(0.0016f, 0.0016f);

		facingLeft = false;

		// Add animations
		std::vector<sf::Vector2i> sequence;
		sequence.push_back(sf::Vector2i(1,1));
		sprite->addAnimation("idle", 9, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector2i(1,2));
		sprite->addAnimation("jump", 60, true, sequence);
		sequence.clear();

		sequence.push_back(sf::Vector2i(2,1));
		sequence.push_back(sf::Vector2i(3,1));
		sequence.push_back(sf::Vector2i(4,1));
		sequence.push_back(sf::Vector2i(5,1));
		sequence.push_back(sf::Vector2i(6,1));
		sequence.push_back(sf::Vector2i(7,1));
		sprite->addAnimation("walk", 9, true, sequence);
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
		sprite->setPosition(position.x * 1 / 10.0f, position.y * 1 / 10.0f);
		
		// Check what animation to play.
		if (!character->isGrounded()) {
			sprite->playAnimation("jump");
		}
		else if (character->isWalking()) {
			sprite->playAnimation("walk");
		} else {
			sprite->playAnimation("idle");
		}

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
	}
}