#include "MainScreenController.h"

MainScreenController::MainScreenController(Screen* mainScreen)
{
    this->mainScreen;
}

MainScreenController::~MainScreenController()
{
    //dtor
}

void MainScreenController::handleInput(sf::Event& event)
{
    // handle input, later on when integrated with Multiplaya project a controller will handle this.

    // handleInput();

    if (event->type == sf::Event::Closed)
        return -1;
    if ((event->type == sf::Event::KeyPressed) && (event->key.code == sf::Keyboard::Escape))
        return -1;

    mainScreen->isMouseOver(sf::Mouse::getPosition(*window));

    if (event->type == sf::Event::MouseButtonReleased)
    {
       // return click( sf::Mouse::getPosition(*window) );
    }
    if (event->type == sf::Event::TextEntered)
    {
        std::cout << "hej" << std::endl;
        //Uint32  c = event->TextEvent.unicode;
        //std::cout << c << std::endl;
    }


}
