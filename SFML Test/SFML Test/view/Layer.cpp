#include "Layer.h"

namespace mp
{
	Layer::Layer(sf::Sprite sprite, const float xSpeed)
	{
		this->sprite;
		this->xSpeed;
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

