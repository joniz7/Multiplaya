#include "Window.h"
#include <iostream>

namespace mp
{
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
		sf::Vector2u resolution = window->getSize();
		screens["mainScreen"] = new MainScreen(resolution);
		screens["joinGameScreen"] = new JoinGameScreen(resolution);
		screens["settingsScreen"] = new SettingsScreen(resolution);
		// will change
		screens["hostScreen"] = new WorldView();

	}

	// run method that draw different screens depending on state

	void Window::run()
	{
		//while (true)
		//{
			window->clear();
			switch (GameState::getInstance()->getGameState())
			{
				case GameState::MAIN_SCREEN:
					window->draw(*screens["mainScreen"]);
				break;

				case GameState::JOIN_GAME:
					window->draw(*screens["joinGameScreen"]);
				break;

				case GameState::HOST_GAME:
					window->draw(*screens["hostScreen"]);
				break;

				case GameState::SETTINGS_SCREEN:
					window->draw(*screens["settingsScreen"]);
				break;
			}

			window->display();
		//}

	}

	sf::RenderWindow* Window::getRenderWindow()
	{
		return window;
	}

	Screen* Window::getScreen(std::string string)
	{
		return screens[string];
	}

	Window::~Window()
	{
		//dtor
	}
}