#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <SFML/Graphics.hpp>

namespace mp
{

	class GUIElement;

	class Screen : public sf::Drawable
	{
		public:
			virtual bool hover (const sf::Vector2i& mousePos) = 0;
			virtual GUIElement* getElement(std::string element) = 0;
			virtual void update() = 0;
		protected:
		private:
	};

}
#endif // SCREEN_H
