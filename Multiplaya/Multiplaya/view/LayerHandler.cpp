#include "LayerHandler.h"

namespace mp
{
	/**
	 * Creates a new LayerHandler.
	 */
	LayerHandler::LayerHandler()
	{
	}

	/**
	 * Adds a new layer to the layer handler.
	 */
	void LayerHandler::addLayer(sf::Sprite sprite, const float xSpeed)
	{
		layers.push_back( Layer( sprite, xSpeed ) );
	}

	/**
	 * Draws all layers in this layer handler to screen.
	 */
	void LayerHandler::draw(sf::RenderTarget& window, sf::RenderStates states) const 
	{
		std::vector<Layer>::const_iterator it;
		for ( it = layers.begin(); it != layers.end(); it++ )
		{
			window.draw(*it);
		}
	}

	/**
	 * Updates all layers in this layer handler.
	 */
	void LayerHandler::update(const float moved)
	{
		std::vector<Layer>::iterator it;
		for ( it = layers.begin(); it < layers.end(); it++ )
		{
			it->update(moved);
		}
	}

	/**
	 * Destroys this LayerHandler.
	 */
	LayerHandler::~LayerHandler() {}
}

