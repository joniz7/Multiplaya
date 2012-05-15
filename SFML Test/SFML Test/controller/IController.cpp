#include "IController.h"

IController::IController(sf::RenderWindow* window, Screen* screen)
{
    this->window = window,
    this->screen = screen;
}

IController::~IController()
{

}

sf::RenderWindow* IController::getRenderWindow()
{
    return window;
}

Screen* IController::getScreen()
{
    return screen;
}
