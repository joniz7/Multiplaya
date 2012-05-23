#include "Window.h"
#include <iostream>

#include "../services/confighandler.h"

namespace mp
{
	// Get screen width from config file
	const float WIDTH = float(ConfigHandler::instance().getInt("r_width"));
	// Get screen height from config file
	const float HEIGHT = float(ConfigHandler::instance().getInt("r_height"));
	// send worlddata in constructor
	Window::Window(WorldData* worldData)
	{
		std::string screenTitle = "Multiplaya";
		initRenderWindow(screenTitle);

		sf::Vector2u resolution = window->getSize();
		initScreens(worldData);		

	}

	/// Draw the main menu
	void Window::drawMainMenu() {
		draw(screens["mainScreen"]);
	}
	/// Draw pause menu
	void Window::drawPauseMenu() {
		draw(screens["pauseScreen"]);
	}
	/// Draw join menu
	void Window::drawJoinMenu() {
		draw(screens["joinGameScreen"]);
	}
	/// Draw the host menu
	void Window::drawHostMenu() {
		draw(screens["hostScreen"]);
	}
	/// Draw the settings menu
	void Window::drawSettingsMenu() {
		draw(screens["settingsScreen"]);
	}
	/// Draw the game screen
	void Window::drawGame()	{
		screens["gameScreen"]->update();
		draw(screens["gameScreen"]);
	}

	
	/**
	* Returns the sfml renderwindow
	* @return the window
	*/
	sf::RenderWindow* Window::getRenderWindow() {
		return window;
	}


	/**
	* Draw the screen to the window.
	* @param screen - the screen to be drawn.
	*/
	void Window::draw(Screen* screen) {
		window->clear();
		window->draw(*screen);
		window->display();
	}

	Screen* Window::getScreen(std::string string) {
		return screens[string];
	}

	void Window::initScreens(WorldData* worldData)
	{
		sf::Vector2u resolution = window->getSize();
		screens["mainScreen"] = new MainScreen(resolution);
		screens["pauseScreen"] = new PauseScreen(resolution);
		screens["joinGameScreen"] = new JoinGameScreen(resolution);
		screens["settingsScreen"] = new SettingsScreen(resolution);
		screens["gameScreen"] = new WorldView(worldData, window);
		screens["hostScreen"] = new HostGameScreen(resolution);
	}

	void Window::initRenderWindow(const std::string screenTitle)
	{
		// if fullscreen set in config file
		if( ConfigHandler::instance().getBool("r_fullscreen") )
			window = new sf::RenderWindow(sf::VideoMode(int(WIDTH), int(HEIGHT), 32), screenTitle, sf::Style::Fullscreen, sf::ContextSettings(0,0,ConfigHandler::instance().getInt("r_antialiasing"),2,0 ) );
		else
			window = new sf::RenderWindow(sf::VideoMode(int(WIDTH), int(HEIGHT), 32), screenTitle, sf::Style::Titlebar, sf::ContextSettings(0,0,ConfigHandler::instance().getInt("r_antialiasing"),2,0 ) );

		window->setFramerateLimit(60);
		// Set window data
        window->setVerticalSyncEnabled(ConfigHandler::instance().getBool("r_vsync"));
        window->setFramerateLimit(ConfigHandler::instance().getInt("r_fpslimit"));
	}

	Window::~Window()
	{
		//dtor
	}
}

