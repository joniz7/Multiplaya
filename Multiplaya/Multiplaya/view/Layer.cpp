#include "Layer.h"
#include <iostream>

namespace mp
{
	Layer::Layer(sf::Sprite sprite, const float xSpeed)
	{
		this->sprite = sprite;
		this->xSpeed = xSpeed;
	}


	Layer::~Layer()
	{
	}

	void Layer::update(const float moved)
	{
		sprite.setPosition(sprite.getPosition().x + moved * xSpeed, sprite.getPosition().y);
	}

	void Layer::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(sprite);
	}
}

