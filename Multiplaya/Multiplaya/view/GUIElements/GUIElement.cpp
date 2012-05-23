#include "GUIElement.h"
#include <iostream>

namespace guielements
{
	/**
	* Create a new GUIElement 
	* @param xPos - Upper left corner's x-position
	* @param yPos - Upper left corner's y-position
	* @param width - Width of button
	* @param height - Height of button
	* @param text - Text in button or empty if none specified
	*/
	GUIElement::GUIElement(const float xPos, const float yPos, const int width, const int height, const std::string text )
	{
		this->xPos = xPos;
		this->yPos = yPos;

		this->width = width;
		this->height = height;

		this->text = new sf::Text(text);
		setTextPosition(5, 5);

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


	/**
	* Setter for text position inside GUIElement
	* When a GUIElement is constructed its font size is set to 30
	* @param xPos - Upper left corner xPos of text
	* @param yPos - Upper left corner yPos of text
	*/
	void GUIElement::setTextPosition(const float x, const float y)
	{
		text->setPosition(xPos + x, yPos + y);
	}

	/**
	* Setter for texts font style
	* By default sf::Style::Regular is chosen
	* @param The style
	*/
	void GUIElement::setFontStyle(sf::Text::Style style)
	{
		text->setStyle(style);
	}


	/**
	* Setter for text size
	* When a GUIElement is constructed its font size is set to 30
	* @param character size
	*/
	void GUIElement::setTextSize(unsigned int size)
	{
		text->setCharacterSize(size);
	}

	/**
	* Setter for font
	* When a GUIElement is constructed a default font is chosen
	* @param the font
	*/
	void GUIElement::setFont(const sf::Font& font)
	{
		text->setFont(font);
	}
			
	/**
	* Setter for the text color
	* By default black is set
	* @param the text
	*/
	void GUIElement::setTextColor(const sf::Color &color)
	{
		text->setColor(color);
	}

	/**
	* Setter for text
	* @return text
	*/
	void GUIElement::setText(const std::string text)
	{
		this->text->setString(text);
	}

	/**
	* Getter for text
	* @return the text
	*/
	const sf::String& GUIElement::getText()
	{
		return text->getString();
	}

	/**
	* Getter for the background color
	* @return background color
	*/
	const sf::Color& GUIElement::getBackgroundColor()
	{
		return background->getFillColor();
	}

	/**
	* Setter for the background color
	* @param the color
	*/
	void GUIElement::setBackgroundColor(const sf::Color &color)
	{
		background->setFillColor(color);
	}

	/**
	* Getter for the border color
	* @return border color
	*/
	const sf::Color& GUIElement::getBorderColor()
	{
		return borderColor;
	}

	/**
	* Setter for the border color
	* When a GUIElement is constructed the border color is set to white by default
	* @param The color
	*/
	void GUIElement::setBorderColor(const sf::Color &color)
	{
		background->setOutlineColor(color);
	}

	/**
	* Getter for border thickness
	* @return border thickness
	*/
	float GUIElement::getBorderThickness()
	{
		return borderThickness;
	}

	/**
	* Setter of borderthickness
	* When a GUIElement is constructed its thickness is set to zero
	* @param the thickness
	*/
	void GUIElement::setBorderThickness(const float thickness)
	{
		background->setOutlineThickness(thickness);
	}

	/**
	* Removes the last character in guielemnt if there is any characters
	*/
	void GUIElement::removeLastCharacter()
	{
		int textLength = getText().getSize();
		if (textLength > 0)
		{
			std::string text = getText();
			setText(text.erase(textLength - 1, 1));
		}
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

	sf::Shape* GUIElement::getBackground()
	{
		return background;
	}

	void GUIElement::setBackgroundAlpha(int alpha)
	{
		background->setFillColor( sf::Color(background->getFillColor().r, background->getFillColor().g, background->getFillColor().b, alpha) );
	}

}