#include "JoinGameController.h"

JoinGameController::JoinGameController(Screen* joinGameScreen)
{
    //ctor
    this->joinGameScreen = joinGameScreen;
    event = new sf::Event();
}

JoinGameController::~JoinGameController()
{
    //dtor
}

void JoinGameController::handleInput(sf::Event& event)
{
    while ( true )
    {
        while (window->pollEvent(*event))
        {
            if (event->type == sf::Event::Closed)
               // return -1;
            if ((event->type == sf::Event::KeyPressed) && (event->key.code == sf::Keyboard::Escape))
                //return -1;

            // put in a function
            connectButton->isMouseOver( sf::Mouse::getPosition(*window) );
            cancelButton->isMouseOver( sf::Mouse::getPosition(*window) );


            if (event->type == sf::Event::MouseButtonReleased)
            {
                //return click( sf::Mouse::getPosition(*window) );
            }
        }

    }
}
