#ifndef BUTTON_H
#define BUTTON_H

#include "GUIElement.h"

namespace mp
{
	class Button : public GUIElement
	{
		public:
			// use vector for pos instead? or the points where button should be placed
			Button(const float xPos, const float yPos, const int width, const int height, std::string text );
			//Button(int xPos, int yPos, int width, int height);

			virtual ~Button();

			void setHoverBorderColor(const sf::Color& color);
			sf::Color& getHoverBorderColor();
			
			void setHoverBorderThickness(const float thickness);
			float getHoverBorderThickness();

			virtual bool isMouseOver(const sf::Vector2i& mousePos);

			virtual void click();
			//getPosition
			//setPosition

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
