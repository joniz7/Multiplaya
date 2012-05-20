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

	void Button::setHoverBorderColor(const sf::Color &color)
	{
		hoverBorderColor = color;
	}

	void Button::setHoverBorderThickness(const float thickness) 
	{
		hoverBorderThickness = thickness;
	}

	float Button::getHoverBorderThickness()
	{
		return hoverBorderThickness;
	}

	// refactor this method like...
	bool Button::isMouseOver(const sf::Vector2i& mousePos)
	{
		// if mouse is over
		if (mouseInsideHitbox(mousePos))
		{
			if (hoverEnabled && !hovering)
			{
				setBackgroundAlpha(getBackground()->getFillColor().a + 40);
				getBackground()->setOutlineColor(hoverBorderColor);
				getBackground()->setOutlineThickness(hoverBorderThickness);
				hovering = true;
			}
			return true;
		}
		// if mouse is not inside hitbox
		if (hoverEnabled && hovering) {
			setBackgroundAlpha(getBackground()->getFillColor().a - 40);
			getBackground()->setOutlineColor(getBorderColor());
			getBackground()->setOutlineThickness(getBorderThickness());
			hovering = false;
		}
		return false;
	}


	void Button::click()
	{
		if (hoverEnabled && hovering) {
			setBackgroundAlpha(getBackground()->getFillColor().a - 40);
			getBackground()->setOutlineColor(getBorderColor());
			getBackground()->setOutlineThickness(getBorderThickness());
			hovering = false;
		}
	}
}