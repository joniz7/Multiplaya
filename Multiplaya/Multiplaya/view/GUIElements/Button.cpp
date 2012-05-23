#include "Button.h"

namespace guielements
{
	// just set size and text, let user set background color and such via methods
	Button::Button(const float xPos, const float yPos, const int width, const int height,
				   std::string text) : GUIElement(xPos,	yPos, width, height, text)
	{
		this->hoverEnabled = true;
		hovering = false;
		hoverBorderColor = sf::Color::Transparent;
		hoverBorderThickness = 0;
	}

	/**
	* Method for enable or disable hovering,
	* if hoverings is disabled no nice effects will be shown on mouse over
	* Default is that hovering is enabled
	* @param hovering
	*/
	void Button::enableHovering(bool hovering)
	{
		hoverEnabled = hovering;
	}

	/**
	* Getter for hovering
	* Default is that hovering is enabled
	* @return Hovering on or off
	*/
	bool Button::hoveringEnabled()
	{
		return hoverEnabled;
	}

	/**
	* Method that returns color of the border when its being hovered
	* @return color
	*/
	const sf::Color& Button::getHoverBorderColor()
	{
		return hoverBorderColor;
	}

	/**
	* Method that returns color of the border when it has been clicked
	* @return color
	*/
	void Button::setHoverBorderColor(const sf::Color &color)
	{
		hoverBorderColor = color;
	}

	/**
	* Method that returns thickness of button when hovering over it
	* @return thickness
	*/
	float Button::getHoverBorderThickness()
	{
		return hoverBorderThickness;
	}

	/**
	* Set thickness of button when hovering over it
	* @param thickness
	*/
	void Button::setHoverBorderThickness(const float thickness) 
	{
		hoverBorderThickness = thickness;
	}

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