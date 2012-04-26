#include "CharacterView.h"

namespace mp
{
	CharacterView::CharacterView(Character* model, sf::Sprite* sprite)
	{
		this->model = model;
		this->sprite = sprite;
	}

	void CharacterView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// Calculate camera position (somehwere between character and mouse)
		b2Vec2 position = model->getBody()->GetPosition();
		float32 angle = model->getBody()->GetAngle();
		sprite->setPosition(position.x * 1 / 10.0f, position.y * 1 / 10.0f);
		target.draw(*sprite, states);
	}

	CharacterView::~CharacterView()
	{
	}
}