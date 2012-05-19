#ifndef LAYER_HANDLER_H
#define LAYER_HANDLER_H

#include <SFML/Graphics.hpp>
#include "Layer.h"
#include <vector>

namespace mp
{
	class LayerHandler : public sf::Drawable
	{
		public:
			LayerHandler();
			~LayerHandler();

			void addLayer(sf::Sprite, const float xSpeed);

			private:
				virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
				std::vector<Layer> layers;
	};
}
#endif