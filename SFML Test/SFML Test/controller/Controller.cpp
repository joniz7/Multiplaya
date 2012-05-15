#include "Controller.h"

Controller::Controller(Window* window)
{
    //ctor
    this->window = window;
    renderWindow = window->getRenderWindow();
    event = new sf::Event();

    controllers["mainScreen"] = new MainScreenController(renderWindow, window->getScreen("mainScreen"));
    controllers["joinGame"] = new JoinGameController(renderWindow, window->getScreen("joinGameScreen"));
  //  controllers["hostGame"] = new HostGameController();
}

Controller::~Controller()
{
    //dtor
}

void Controller::run()
{
    //while (true)
    //{
       while (renderWindow->pollEvent(*event))
       {

            if (event->type == sf::Event::Closed)
                renderWindow->close();
            if ((event->type == sf::Event::KeyPressed) && (event->key.code == sf::Keyboard::Escape))
                renderWindow->close();


            switch (GameState::getInstance()->getGameState())
            {
                case GameState::MAIN_SCREEN:
                    controllers["mainScreen"]->handleInput(*event);
                break;

                case GameState::JOIN_GAME:
                    controllers["joinGame"]->handleInput(*event);
                break;

                case GameState::HOST_GAME:

                break;

                case GameState::SETTINGS_SCREEN:

                break;


            }
       }
    //}
}
