#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <sfml/Graphics.hpp>
#include <string>

namespace mp
{
	class GUIElement : public sf::Drawable
	{
		public:
			enum TextAlignment {
			  LEFT,
			  CENTER,
			  RIGHT
		   };

			GUIElement(const float xPos, const float yPos, const int width, const int height, const std::string text = "" );

			virtual ~GUIElement();

			void setBackgroundColor(const sf::Color &color);
			const sf::Color& getBackgroundColor();

			void setBorderColor(const sf::Color &color);
			const sf::Color& getBorderColor();
			void setBorderThickness(const float thickness);
			float getBorderThickness();

			virtual bool isMouseOver(const sf::Vector2i& mousePos) = 0;
			// Look into the possibility to send function pointer
			virtual void click() = 0;

			virtual void setFont(const sf::Font &font);
			virtual void setFontSize(unsigned int size);
			virtual void setFontColor(const sf::Color &color);
			void setFontStyle(sf::Text::Style style);
			
			virtual void setText(const std::string text);
			const sf::String& getText();
			void setTextAlignment(TextAlignment alignment);
					
			void setTextPosition(const float x, const float y);

		protected:
			virtual bool mouseInsideHitbox(const sf::Vector2i& mousePos);
			void setBackgroundAlpha(int alpha);
			sf::Shape* getBackground();
		private:
			void init(const float xPos, const float yPos, const int width, const int height);
			float xPos;
			float yPos;
			int width;
			int height;

			sf::Shape* background;
			sf::Color backgroundColor;
			sf::Text* text;

			sf::Color borderColor;
			float borderThickness;

			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	};
}
#endif // GUIELEMENT_H
