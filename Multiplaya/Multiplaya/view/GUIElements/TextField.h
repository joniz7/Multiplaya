#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "GUIElement.h"

namespace mp
{
	class TextField : public GUIElement
	{
		public:
			TextField(const float xPos, const float yPos, const int width, const int height);
			virtual ~TextField();

			virtual bool isMouseOver(const sf::Vector2i& mousePos);
			virtual void click();
			bool isClicked();
			// set text input to left and middle in height all the time

			void setBorderColorClicked(const sf::Color& color);
			const sf::Color& getBorderColorClicked();

			void setBorderThicknessClicked(float thickness);
			float getBorderThicknessClicked();

		protected:
		private:
			bool clicked;
			sf::Color borderColorClicked;
			float borderThicknessClicked;
	};
}

#endif // TEXTFIELD_H
