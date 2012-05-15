#ifndef JOINGAMECONTROLLER_H
#define JOINGAMECONTROLLER_H

#include "IController.h"
#include "JoinGameScreen.h"
#include <iostream>

class JoinGameController : public IController
{
    public:
        JoinGameController(sf::RenderWindow* window, Screen* joinGameScreen);
        virtual ~JoinGameController();
        void handleInput(sf::Event &event);
    protected:
    private:

        bool ipTextClicked;
        bool portTextClicked;

        bool isNumberOrDot(sf::Event &event);

        GUIElement* cancelButton;
        GUIElement* connectButton;

        GUIElement* ipTextField;
        GUIElement* portTextField;

};

#endif // JOINGAMECONTROLLER_H
