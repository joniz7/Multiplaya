#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <SFML/Graphics.hpp>
#include <string>

namespace mp
{
	/**
	 * Abstract class representing a GUIElement with text inside it
	 */
	class GUIElement : public sf::Drawable
	{
		public:
			// enum for placing text inside an element, not yet implemented TODO
			enum TextAlignment {
			  LEFT,
			  CENTER,
			  RIGHT
		   };

			GUIElement(const float xPos, const float yPos, const int width, const int height, const std::string text = "" );

			virtual ~GUIElement();

			const sf::Color& getBackgroundColor();
			void setBackgroundColor(const sf::Color &color);

			const sf::Color& getBorderColor();
			void setBorderColor(const sf::Color &color);

			float getBorderThickness();
			void setBorderThickness(const float thickness);

			virtual void setFont(const sf::Font &font);
			void setFontStyle(sf::Text::Style style);

			virtual void setTextSize(unsigned int size);
			virtual void setTextColor(const sf::Color &color);
			void setTextPosition(const float x, const float y);
			// For auto aligning, see TextAlignment enum
			void setTextAlignment(TextAlignment alignment);
			
			const sf::String& getText();
			virtual void setText(const std::string text);

			void removeLastCharacter();

			/**
			* Checks if mouse is hovering over the element
			* @param the mouse position
			* @return background color
			*/
			virtual bool isMouseOver(const sf::Vector2i& mousePos) = 0;
			
			/**
			* Activates events / effects that is set to that element
			*/
			virtual void click() = 0;

			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

		protected:
			virtual bool mouseInsideHitbox(const sf::Vector2i& mousePos);
			
			sf::Shape* getBackground();
			void setBackgroundAlpha(int alpha);

		private:
			float xPos;
			float yPos;
			int width;
			int height;

			sf::Shape* background;
			sf::Color backgroundColor;

			sf::Text* text;

			sf::Color borderColor;
			float borderThickness;



	};
}
#endif // GUIELEMENT_H
