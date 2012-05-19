#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>

namespace mp
{
	class Layer : public sf::Drawable
	{
		public:
			Layer(sf::Sprite sprite, const float xSpeed);
			~Layer();
		private:
			sf::Sprite sprite;
			float xSpeed;
			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
			void update();
	};
}
#endif
