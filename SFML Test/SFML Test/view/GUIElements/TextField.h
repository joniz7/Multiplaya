#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "GUIElement.h"
#include <string>

namespace mp
{
	class TextField : public GUIElement
	{
		public:
			TextField(const float xPos, const float yPos, const int width, const int height);
			virtual ~TextField();

			void setText(std::string text);
			const sf::String& getText() { return text->getString(); }

			void setBorderColor(const sf::Color &color);
			void setBorderThickness(const float thickness);
			void setBackgroundColor(const sf::Color &color);

			virtual void setFont(const sf::Font &font) {}
			virtual void setFontColor(const sf::Color &color) {}

			void setHoverBorder();

			sf::Color getBackgroundColor();

			void setFontColor();
			void setFontSize();

			virtual bool isMouseOver(const sf::Vector2i& mousePos);
			virtual void click();
			// set text input to left and middle in height all the time

		protected:
		private:
			float xPos;
			float yPos;
			int width;
			int height;

			sf::Shape* background;
			sf::Text* text;

			bool hoverEnabled;
			bool hovering;


			bool clicked;
			//sf::Color borderColorClicked;

			void borderColorClicked(sf::Color& color);

			bool mouseInsideHitbox(const sf::Vector2i& mousePos);

			void setBackgroundAlpha(int alpha);
			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
	};
}

#endif // TEXTFIELD_H
