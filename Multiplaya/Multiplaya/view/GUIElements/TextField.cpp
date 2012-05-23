#include "TextField.h"
#include <iostream>

namespace guielements
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

	/**
	* Method that returns color of the border when it has been clicked
	* @return color
	*/
	const sf::Color& TextField::getBorderColorClicked()
	{
		return borderColorClicked;
	}

	/**
	* Set color of border when it's clicked
	* @param color
	*/
	void TextField::setBorderColorClicked(const sf::Color& color)
	{
		borderColorClicked = color;
	}

	/**
	* Method that returns thickness of the border when it has been clicked
	* @return thickness
	*/
	float TextField::getBorderThicknessClicked()
	{
		return borderThicknessClicked;
	}

	/**
	* Set thickness of border when it has been clicked
	* @param thickness
	*/
	void TextField::setBorderThicknessClicked(float thickness) {
		borderThicknessClicked = thickness;
	}

	bool TextField::isMouseOver(const sf::Vector2i& mousePos)
	{
		// if mouse is over
		if (mouseInsideHitbox(mousePos))
			return true;
		return false;
	}

	/**
	* Method that checks if text field has been clicked
	* @return true if has been clicked
	*/
	bool TextField::isClicked()
	{
		return clicked;
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
}