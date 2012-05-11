#include "JoinGameScreen.h"

JoinGameScreen::JoinGameScreen()
{
    font = new sf::Font();
    font->loadFromFile("resources/gothic.ttf");


    screenTitleText = new sf::Text("Connect to server");
    screenTitleText->setFont(*font);
    screenTitleText->setStyle(sf::Text::Bold);
    screenTitleText->setColor(sf::Color::White);
    screenTitleText->setPosition(400, 20);
    screenTitleText->setCharacterSize(40);

    background = new sf::RectangleShape( sf::Vector2f(this->window->getSize().x, this->window->getSize().y) );
    background->setFillColor( sf::Color(94, 94, 94, 255) );
    background->setPosition(0, 0);

    connectButton = new Button(40, 100, 200, 60, "Connect");
    connectButton->setFont(*font);
    connectButton->setFontColor(sf::Color::Black);

    cancelButton = new Button(40, 180, 200, 60, "Cancel");
    cancelButton->setFont(*font);
    cancelButton->setFontColor(sf::Color::Black);

}

JoinGameScreen::~JoinGameScreen()
{
    //dtor
}

void JoinGameScreen::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(*background);
    window.draw(*connectButton);
    window.draw(*cancelButton);
    window.draw(*screenTitleText);
}
