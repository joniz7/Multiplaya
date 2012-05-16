#include "GUIElement.h"

namespace mp
{
	GUIElement::GUIElement(const float xPos, const float yPos, const int width, const int height, std::string text )
	{
		init(xPos, yPos, width, height);
		this->text->setString(text);
	}

	GUIElement::GUIElement(const float xPos, const float yPos, const int width, const int height )
	{
		init(xPos, yPos, width, height);
	}

	void GUIElement::init(const float xPos, const float yPos, const int width, const int height)
	{
		this->xPos = xPos;
		this->yPos = yPos;

		this->width = width;
		this->height = height;

		this->text = new sf::Text();
		this->text->setPosition(xPos + 5, yPos + 5);
	   // alignment = CENTER;

		background = new sf::RectangleShape( sf::Vector2f(width, height));
		background->setPosition(xPos, yPos);
	}

	GUIElement::~GUIElement()
	{
		delete background;
		delete text;
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

}