#include "LayerHandler.h"

namespace mp
{
	LayerHandler::LayerHandler()
	{
	}

	void LayerHandler::addLayer(sf::Sprite sprite, const float xSpeed)
	{
		layers.push_back( Layer( sprite, xSpeed ) );
	}

	void LayerHandler::draw(sf::RenderTarget& window, sf::RenderStates states) const 
	{
		std::vector<Layer>::const_iterator it;
		for ( it = layers.begin(); it != layers.end(); it++ )
		{
			window.draw(*it);
		}
	}

	void LayerHandler::update(const float moved)
	{
		std::vector<Layer>::iterator it;
		for ( it = layers.begin(); it < layers.end(); it++ )
		{
			it->update(moved);
		}
	}

	LayerHandler::~LayerHandler()
	{
	}
}

