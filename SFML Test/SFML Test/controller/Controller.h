#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "GameState.h"
#include "Window.h"
#include "MainScreenController.h"
#include "HostGameController.h"
#include "JoinGameController.h"

class Controller
{
    public:
        Controller(Window* window);
        virtual ~Controller();
        void run();
    protected:
    private:
        //alternative is a map
        sf::Event* event;
        //std::vector<IController*> controllers;
        std::map<std::string, IController*> controllers;
        Window* window;
        sf::RenderWindow* renderWindow;

        // sf window reference
};

#endif // CONTROLLER_H
