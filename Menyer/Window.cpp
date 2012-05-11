#include "Window.h"

Window::Window()
{
    //ctor
    window = new sf::RenderWindow(sf::VideoMode(1200, 600, 32), "Multiplaya");
    window->setFramerateLimit(60);

    /*
    screens.push_back( new MainScreen() );
    screens.push_back( new JoinGameScreen() );
    screens.push_back ( new SettingsScreen() );
    */
    screens["mainScreen"] = new MainScreen();
    screens["joinGameScreen"] = new JoinGameScreen();
    screens["settingsScreen"] = new SettingsScreen();

}

// run method that draw different screens depending on state

void Window::run()
{
    while (true)
    {
        window->clear();

        switch (gameState)
        {
            case MAIN_SCREEN:
                window->draw(screens["mainScreen"]);
            break;

            case JOIN_GAME:
                window->draw(screens["joinGameScreen"]);
            break;

            case SETTINGS_SCREEN:
                window->draw(screens["settingsScreen"]);
            break;
        }

        window->display();
    }

}

sf::RenderWindow* Window::getRenderWindow()
{
    return window;
}

Screen* Window::getScreen(std::string)
{
    return screens[string];
}

Window::~Window()
{
    //dtor
}
