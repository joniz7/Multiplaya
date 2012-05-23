#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>

namespace mp
{
	/**
	 * Represents a background layer. Is used by LayerHandler.
	 */
	class Layer : public sf::Drawable
	{
		public:
			Layer(sf::Sprite sprite, const float xSpeed);
			~Layer();
			void update(const float moved);
		private:
			sf::Sprite sprite;
			float xSpeed;
			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	};
}
#endif
