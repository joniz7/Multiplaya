#include "TextField.h"
#include <iostream>

namespace mp
{
	TextField::TextField(const float xPos, const float yPos, const int width, const int height)
	{
		this->xPos = xPos;
		this->yPos = yPos;

		this->width = width;
		this->height = height;

		background = new sf::RectangleShape( sf::Vector2f(width, height) );
		background->setPosition(xPos, yPos);

		text = new sf::Text();
		text->setPosition(xPos + 5, yPos + 5);
		text->setColor(sf::Color::Black);
		hoverEnabled = true;
		hovering = false;
		clicked = false;
		//ctor
	}

	TextField::~TextField()
	{
		//dtor
		delete background;
		delete text;
	}

	void TextField::setText(std::string text)
	{
		this->text->setString(text);
	}

	void TextField::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(*background, states);
		window.draw(*text, states);
	}

	bool TextField::isMouseOver(const sf::Vector2i& mousePos)
	{
		// if mouse is over, increase font size a bi
		if (mouseInsideHitbox(mousePos))
		{
		   /* if (hoverEnabled && !hovering)
			{
				setBackgroundAlpha(background->getFillColor().a + 20);
				hovering = true;
			}*/
			return true;
		}
		// if mouse is not inside hitbox
		/*if (hoverEnabled && hovering) {
			setBackgroundAlpha(background->getFillColor().a - 20);
			hovering = false;
		}*/
		return false;
	}

	void TextField::click()
	{
		if (!clicked)
		{
			background->setOutlineThickness(1);
			background->setOutlineColor(sf::Color::Red);
			clicked = true;
		}
		else
		{
			background->setOutlineThickness(0);
			clicked = false;
		}

	}

	void TextField::setBackgroundAlpha(int alpha)
	{
		background->setFillColor( sf::Color(background->getFillColor().r, background->getFillColor().g, background->getFillColor().b, alpha) );
	}

	bool TextField::mouseInsideHitbox(const sf::Vector2i& mousePos)
	{
		return (mousePos.x > xPos) && (mousePos.y > yPos) &&
				 (mousePos.x < xPos + width) && (mousePos.y < yPos + height);
	}

}