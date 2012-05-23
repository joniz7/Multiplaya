#ifndef BUTTON_H
#define BUTTON_H

#include "GUIElement.h"

namespace guielements
{
	/**
	 * Class representing a button
	 */
	class Button : public GUIElement
	{
		public:
			Button(const float xPos, const float yPos, const int width, const int height, std::string text );
			virtual ~Button();

			const sf::Color& getHoverBorderColor();
			void setHoverBorderColor(const sf::Color& color);
			
			void setHoverBorderThickness(const float thickness);
			float getHoverBorderThickness();

			virtual bool isMouseOver(const sf::Vector2i& mousePos);

			virtual void click();
		protected:
		private:
			sf::Color hoverBorderColor;
			float hoverBorderThickness;

			// TODO setters and getters for hover enabled
			bool hoverEnabled;
			bool hovering;
	};
}
#endif // BUTTON_H
