#include "Button.h"

namespace mp
{
	// just set size and text, let user set background color and such via methods
	Button::Button(const float xPos, const float yPos, const int width, const int height,
				   std::string text) : GUIElement(xPos,	yPos, width, height, text)
	{
		this->hoverEnabled = true;
		hovering = false;
	}

	Button::~Button()
	{
		//dtor
	}


	// refactor this method like...
	bool Button::isMouseOver(const sf::Vector2i& mousePos)
	{
		// if mouse is over, increase font size a bi
		if (mouseInsideHitbox(mousePos))
		{
			if (hoverEnabled && !hovering)
			{
				setBackgroundAlpha(getBackground()->getFillColor().a + 40);
				hovering = true;
			}
			return true;
		}
		// if mouse is not inside hitbox
		if (hoverEnabled && hovering) {
			setBackgroundAlpha(getBackground()->getFillColor().a - 40);
			hovering = false;
		}
		return false;
	}


	void Button::click()
	{
		if (hoverEnabled && hovering) {
			setBackgroundAlpha(getBackground()->getFillColor().a - 40);
			hovering = false;
		}
	}

}