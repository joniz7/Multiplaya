#include "TextField.h"
#include <iostream>

namespace mp
{
	TextField::TextField(const float xPos, const float yPos, const int width, const int height) : GUIElement(xPos, yPos, width, height)
	{
		clicked = false;
		//ctor
	}

	TextField::~TextField()
	{
		//dtor

	}

	bool TextField::isMouseOver(const sf::Vector2i& mousePos)
	{
		// if mouse is over
		if (mouseInsideHitbox(mousePos))
			return true;
		return false;
	}

	void TextField::click()
	{
		if (!clicked)
		{
			getBackground()->setOutlineThickness(borderThicknessClicked);
			getBackground()->setOutlineColor(borderColorClicked);
			clicked = true;
		}
		else
		{
			getBackground()->setOutlineThickness(getBorderThickness());
			getBackground()->setOutlineColor(getBorderColor());
			clicked = false;
		}
	}

	void TextField::setBorderColorClicked(const sf::Color& color)
	{
		borderColorClicked = color;
	}
	const sf::Color& TextField::getBorderColorClicked()
	{
		return borderColorClicked;
	}


	float TextField::getBorderThicknessClicked()
	{
		return borderThicknessClicked;
	}

	
	void TextField::setBorderThicknessClicked(float thickness) {
		borderThicknessClicked = thickness;
	}
}