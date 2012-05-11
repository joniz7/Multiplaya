#ifndef JOINGAMECONTROLLER_H
#define JOINGAMECONTROLLER_H

#include "IController.h"
#include "JoinGameScreen.h"

class JoinGameController : public IController
{
    public:
        JoinGameController(Screen* joinGameScreen);
        virtual ~JoinGameController();
        void handleInput(sf::Event& event);
    protected:
    private:
        Screen* joinGameScreen;

};

#endif // JOINGAMECONTROLLER_H
