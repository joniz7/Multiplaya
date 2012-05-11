#ifndef WINDOW_H
#define WINDOW_H


#include <string>
#include "GameState.h"

#include "Screen.h"
#include "MainScreen.h"
#include "JoinGameScreen.h"
#include "SettingsScreen.h"

class Window
{
    public:
        Window();
        virtual ~Window();
        void run();

        Screen* getScreen(std::string);
        sf::RenderWindow* getRenderWindow();
    protected:
    private:
        sf::RenderWindow* window;
       // std::vector<Screen*> screens;
       std::map<std::string, Screen*> screens;
};

#endif // WINDOW_H
