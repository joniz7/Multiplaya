#include "TextField.h"

TextField::TextField(const float xPos, const float yPos, const int width, const int height)
{
    background = new sf::RectangleShape( sf::Vector2f(width, height) );
    background->setPosition(xPos, yPos);

    text = new sf::Text();
    text->setPosition(xPos, yPos);
    text->setColor(sf::Color::Black);
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
