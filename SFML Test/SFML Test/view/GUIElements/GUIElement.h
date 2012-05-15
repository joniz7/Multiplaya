#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <sfml/Graphics.hpp>

namespace mp
{
	class GUIElement : public sf::Drawable
	{
		public:
			virtual bool isMouseOver(const sf::Vector2i& mousePos) = 0;
			// Look into the possibility to send function pointer
			virtual void click() = 0;

			virtual void setFont(const sf::Font &font) = 0;
			virtual void setFontColor(const sf::Color &color) = 0;

			virtual void setText(std::string text) = 0;
			virtual const sf::String& getText() = 0;
		protected:
		private:
	};
}
#endif // GUIELEMENT_H
