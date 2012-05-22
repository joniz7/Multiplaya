#include "GUIElement.h"
#include <iostream>

namespace mp
{
	GUIElement::GUIElement(const float xPos, const float yPos, const int width, const int height, const std::string text )
	{
		this->xPos = xPos;
		this->yPos = yPos;

		this->width = width;
		this->height = height;

		this->text = new sf::Text(text);
		setTextPosition(5, 5);
	   // alignment = CENTER;

		background = new sf::RectangleShape( sf::Vector2f(float(width), float(height)));
		borderThickness = 0;
		background->setOutlineThickness(borderThickness);
		borderColor = sf::Color::White;
		background->setOutlineColor(borderColor);
		background->setPosition(xPos, yPos);
	}

	GUIElement::~GUIElement()
	{
		delete background;
		delete text;
	}

	void GUIElement::setTextPosition(const float x, const float y)
	{
		text->setPosition(xPos + x, yPos + y);
	}

	void GUIElement::setFontStyle(sf::Text::Style style)
	{
		text->setStyle(style);
	}

	void GUIElement::setFontSize(unsigned int size)
	{
		text->setCharacterSize(size);
	}

	void GUIElement::setFont(const sf::Font& font)
	{
		text->setFont(font);
	}

	void GUIElement::setFontColor(const sf::Color &color)
	{
		text->setColor(color);
	}

	void GUIElement::setTextAlignment(TextAlignment alignment)
	{
	//    this->alignment = aligment;
	}

	void GUIElement::setText(const std::string text)
	{
		this->text->setString(text);
	}

	const sf::String& GUIElement::getText()
	{
		return text->getString();
	}

	void GUIElement::setBackgroundColor(const sf::Color &color)
	{
		background->setFillColor(color);
	}

	const sf::Color& GUIElement::getBackgroundColor()
	{
		return background->getFillColor();
	}

	void GUIElement::setBorderColor(const sf::Color &color)
	{
		background->setOutlineColor(color);
	}

	const sf::Color& GUIElement::getBorderColor()
	{
		return borderColor;
	}

	float GUIElement::getBorderThickness()
	{
		return borderThickness;
	}

	void GUIElement::setBorderThickness(const float thickness)
	{
		background->setOutlineThickness(thickness);
	}

	void GUIElement::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(*background, states);
		window.draw(*text, states);
	}

	bool GUIElement::mouseInsideHitbox(const sf::Vector2i& mousePos)
	{
		return (mousePos.x > xPos) && (mousePos.y > yPos) &&
				 (mousePos.x < xPos + width) && (mousePos.y < yPos + height);
	}

	void GUIElement::setBackgroundAlpha(int alpha)
	{
		background->setFillColor( sf::Color(background->getFillColor().r, background->getFillColor().g, background->getFillColor().b, alpha) );
	}

	sf::Shape* GUIElement::getBackground()
	{
		return background;
	}

	void GUIElement::removeLastCharacter()
	{
		int textLength = getText().getSize();
		if (textLength > 0)
		{
			std::string text = getText();
			setText(text.erase(textLength - 1, 1));
		}
	}
}