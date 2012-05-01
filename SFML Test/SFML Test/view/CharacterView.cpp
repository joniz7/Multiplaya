#include "CharacterView.h"

namespace mp
{
	//CharacterView::CharacterView(Character* model, sf::Sprite* sprite)
	CharacterView::CharacterView(Character* model, AnimatedSprite* sprite)
	{
		this->model = model;
		this->sprite = sprite;
	}

	void CharacterView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		b2Vec2 position = model->getBody()->GetPosition();
		float32 angle = model->getBody()->GetAngle();
		sprite->setPosition(position.x * 1 / 10.0f, position.y * 1 / 10.0f);
		target.draw(*sprite, states);
	}

	void CharacterView::notify(std::string e, void* object)
	{
		std::cout << "aa" << std::endl;
		if (e == "walking")
		{
			sprite->playAnimation("walk");
		} 
		else if (e == "idle")
		{
			sprite->playAnimation("idle");
		}
	}

	CharacterView::~CharacterView()
	{
	}
}