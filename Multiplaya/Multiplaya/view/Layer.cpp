#include "Layer.h"
#include <iostream>

namespace mp
{
	/**
	 * Creates a new background layer.
	 *
	 * @param sprite - The sprite used for the background layer.
	 * @param xSpeed - the speed factor this layer should scroll with.
	 */
	Layer::Layer(sf::Sprite sprite, const float xSpeed) {
		this->sprite = sprite;
		this->xSpeed = xSpeed;
	}

	/**
	 * Destructor.
	 */
	Layer::~Layer()
	{
	}

	/**
	 * Update the position of the layer.
	 */
	void Layer::update(const float moved)
	{
		sprite.setPosition(sprite.getPosition().x + moved * xSpeed, sprite.getPosition().y);
	}

	/**
	 * Draws the layer to screen.
	 */
	void Layer::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(sprite);
	}
}

