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

	void Layer::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(sprite);
	}
}

