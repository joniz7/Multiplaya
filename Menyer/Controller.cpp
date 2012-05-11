#include "Controller.h"

Controller::Controller(Window* window)
{
    //ctor
    this->window = window;
    event = new sf::Event();

    controllers["mainScreen"] = new MainScreenController(window->getScreen("mainScreen"));
    controllers["joinGame"] = new JoinGameController("joinGameScreen");
    controllers["hostGame"] = new HostGame();

   /* controllers.push_back( new MainScreenController() );
    controllers.push_back( new JoinGameController() );
    controllers.push_back( new HostGameController() );

    */
}

Controller::~Controller()
{
    //dtor
}

void Controller::run()
{
    while (true)
    {
       while (window->pollEvent(*event))
       {
            switch (gameState)
            {
                case MAIN_SCREEN:

                break;

                case JOIN_GAME:

                break;

                case HOST_GAME:

                break;
            }
       }
    }
}
