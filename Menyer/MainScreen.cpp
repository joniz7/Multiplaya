#include "MainScreen.h"

#include <iostream>

MainScreen::MainScreen()
{
    // do I choose a sf::Texture or an sf::Image?
    backgroundTexture = new sf::Texture();
    backgroundTexture->loadFromFile("resources/background.jpg");

    backgroundSprite = new sf::Sprite();
    backgroundSprite->setTexture(*backgroundTexture);
    backgroundSprite->setPosition(0, 0);

    // calculate background sprite scaling
    // move to method later on
    backgroundSprite->scale( 2.0f,  1.0f);

    font = new sf::Font();
    font->loadFromFile("resources/gothic.ttf");

    gameTitleText = new sf::Text("Multiplaya");
    gameTitleText->setFont(*font);
    gameTitleText->setStyle(sf::Text::Bold);
    gameTitleText->setColor(sf::Color::Black);
    gameTitleText->setPosition(500, 20);
    gameTitleText->setCharacterSize(40);


    joinGameButton = new Button(40, 100, 200, 60, "Join game");
    joinGameButton->setFont(*font);
    joinGameButton->setFontColor(sf::Color::Black);

    hostGameButton = new Button(40, 180, 200, 60, "Host game");
    hostGameButton->setFont(*font);
    hostGameButton->setFontColor(sf::Color::Black);

    settingsButton = new Button(40, 260, 200, 60, "Settings");
    settingsButton->setFont(*font);
    settingsButton->setFontColor(sf::Color::Black);

    exitGameButton = new Button(40, 340, 200, 60, "Exit game");
    exitGameButton->setFont(*font);
    exitGameButton->setFontColor(sf::Color::Black);

    textField = new TextField( 400, 200, 100, 50);
    textField->setText("Testar");

}

MainScreen::~MainScreen()
{
    delete gameTitleText;
    delete joinGameButton;
    delete hostGameButton;
    delete settingsButton;
    delete exitGameButton;
    delete font;
}

void MainScreen::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(*backgroundSprite);
    window.draw(*gameTitleText);

    // draw buttons
    window.draw(*joinGameButton);
    window.draw(*hostGameButton);
    window.draw(*settingsButton);
    window.draw(*exitGameButton);

    window.draw(*textField);
}

int MainScreen::click(const sf::Vector2i& mousePos)
{
    if ( joinGameButton->isMouseOver( mousePos ) )
    {
        std::cout << "Join game" << std::endl;

        return 1;
    }
    else if ( hostGameButton->isMouseOver( mousePos ) )
    {
        std::cout << "host game" << std::endl;
    }
    else if ( settingsButton->isMouseOver( mousePos ) )
    {
        std::cout << "settings" << std::endl;
    }
    else if ( exitGameButton->isMouseOver( mousePos ) )
    {
        std::cout << "exit game" << std::endl;
    }

    return 0;
}

bool MainScreen::isMouseOver(const sf::Vector2i& mousePos)
{
    // put in a function
    joinGameButton->isMouseOver( mousePos );
    hostGameButton->isMouseOver( mousePos );
    settingsButton->isMouseOver( mousePos );
    exitGameButton->isMouseOver( mousePos );

}
