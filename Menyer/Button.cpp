#include "Button.h"

// just set size and text, let user set background color and such via methods
Button::Button(const float xPos, const float yPos, const int width, const int height,
               std::string text)
{
    this->xPos = xPos;
    this->yPos = yPos;

    this->width = width;
    this->height = height;

    this->text = new sf::Text(text);
    this->text->setPosition(xPos + 5, yPos + 5);
   // alignment = CENTER;
    this->hoverEnabled = true;

    background = new sf::RectangleShape( sf::Vector2f(width, height));
    background->setPosition(xPos, yPos);

    hovering = false;
}

Button::~Button()
{
    //dtor
}

void Button::setFontStyle(sf::Text::Style style)
{
    text->setStyle(style);
}

void Button::setFontSize(unsigned int size)
{
    text->setCharacterSize(size);
}

void Button::setFont(const sf::Font& font)
{
    text->setFont(font);
}

void Button::setFontColor(const sf::Color &color)
{
    text->setColor(color);
}

void Button::setTextAlignment(TextAlignment alignment)
{
//    this->alignment = aligment;
}

void Button::setBackgroundColor(const sf::Color &color)
{
    background->setFillColor(color);
}

void Button::setBorderColor(const sf::Color &color)
{
    background->setOutlineColor(color);
}

void Button::setBorderThickness(const float thickness)
{
    background->setOutlineThickness(thickness);
}


// refactor this method like...
bool Button::isMouseOver(const sf::Vector2i& mousePos)
{
    // if mouse is over, increase font size a bi
    if (mouseInsideHitbox(mousePos))
    {
        if (hoverEnabled && !hovering)
        {
            setBackgroundAlpha(background->getFillColor().a + 40);
            hovering = true;
        }
        return true;
    }
    // if mouse is not inside hitbox
    if (hoverEnabled && hovering) {
        setBackgroundAlpha(background->getFillColor().a - 40);
        hovering = false;
    }
    return false;
}

/*
void Button::click()
{

}
*/

bool Button::mouseInsideHitbox(const sf::Vector2i& mousePos)
{
    return (mousePos.x > xPos) && (mousePos.y > yPos) &&
             (mousePos.x < xPos + width) && (mousePos.y < yPos + height);
}

void Button::setBackgroundAlpha(int alpha)
{
    background->setFillColor( sf::Color(background->getFillColor().r, background->getFillColor().g, background->getFillColor().b, alpha) );
}



void Button::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(*background, states);
    window.draw(*text, states);

}

void Button::setText(const std::string text)
{
    this->text->setString(text);
}
