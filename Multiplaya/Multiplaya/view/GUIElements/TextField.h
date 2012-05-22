#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "GUIElement.h"

namespace mp
{
	/**
	 * Class representing a text field
	 */
	class TextField : public GUIElement
	{
		public:
			TextField(const float xPos, const float yPos, const int width, const int height);
			virtual ~TextField();

			bool isClicked();

			void setBorderColorClicked(const sf::Color& color);
			const sf::Color& getBorderColorClicked();
			void setBorderThicknessClicked(float thickness);
			float getBorderThicknessClicked();

			virtual bool isMouseOver(const sf::Vector2i& mousePos);
			virtual void click();

		protected:
		private:
			bool clicked;
			sf::Color borderColorClicked;
			float borderThicknessClicked;
	};
}

#endif // TEXTFIELD_H
