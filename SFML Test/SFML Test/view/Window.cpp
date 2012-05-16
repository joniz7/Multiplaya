#include "Window.h"
#include <iostream>

#include "../services/confighandler.h"

namespace mp
{
	const float WIDTH = ConfigHandler::instance().getInt("r_width");
	const float HEIGHT = ConfigHandler::instance().getInt("r_height");
	// send worlddata in constructor
	Window::Window(WorldData* worldData)
	{
		//ctor
		window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT, 32), "Multiplaya");
		window->setFramerateLimit(60);
		// Set window data
        window->setVerticalSyncEnabled(ConfigHandler::instance().getBool("r_vsync"));
        window->setFramerateLimit(ConfigHandler::instance().getInt("r_fpslimit"));

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
		screens["hostScreen"] = new WorldView(worldData, window);
		worldView = (WorldView*) screens["hostScreen"];


	}

	// run method that draw different screens depending on state

	void Window::exec()
	{

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
				worldView->update();
				window->draw(*screens["hostScreen"]);
			break;

			case GameState::SETTINGS_SCREEN:
				window->draw(*screens["settingsScreen"]);
			break;
		}

		window->display();
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