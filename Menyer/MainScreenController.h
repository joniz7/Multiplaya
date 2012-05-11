#ifndef MAINSCREENCONTROLLER_H
#define MAINSCREENCONTROLLER_H

#include "IController.h"
#include "MainScreen.h"

class MainScreenController : public IController
{
    public:
        MainScreenController(Screen* mainScreen);
        virtual ~MainScreenController();
        void handleInput(sf::Event& event);
    protected:
    private:
        Screen* mainScreen;

};

#endif // MAINSCREENCONTROLLER_H
