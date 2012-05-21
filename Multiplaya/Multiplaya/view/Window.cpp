#include "Window.h"
#include <iostream>

#include "../services/confighandler.h"

namespace mp
{
	const float WIDTH = float(ConfigHandler::instance().getInt("r_width"));
	const float HEIGHT = float(ConfigHandler::instance().getInt("r_height"));
	// send worlddata in constructor
	Window::Window(WorldData* worldData)
	{
		//ctor
		//window = new sf::RenderWindow(sf::VideoMode(int(WIDTH), int(HEIGHT), 32), "Multiplaya");
		const std::string WINDOW_TITLE = "Multiplaya";
		if( ConfigHandler::instance().getBool("r_fullscreen") )
			window = new sf::RenderWindow(sf::VideoMode(int(WIDTH), int(HEIGHT), 32), WINDOW_TITLE, sf::Style::Fullscreen, sf::ContextSettings(0,0,ConfigHandler::instance().getInt("r_antialiasing"),2,0 ) );
		else
			window = new sf::RenderWindow(sf::VideoMode(int(WIDTH), int(HEIGHT), 32), WINDOW_TITLE, sf::Style::Titlebar, sf::ContextSettings(0,0,ConfigHandler::instance().getInt("r_antialiasing"),2,0 ) );

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
		screens["gameScreen"] = new WorldView(worldData, window);
		screens["hostScreen"] = new HostGameScreen(resolution);
		

	}

	// run method that draw different screens depending on state

	void Window::drawMainMenu() {
		draw(screens["mainScreen"]);
	}
	void Window::drawInGame() {
		// TODO 	
	}
	void Window::drawInGameMenu() {
		// TODO
	}
	void Window::drawJoinMenu() {
		draw(screens["joinGameScreen"]);
	}
	void Window::drawHostMenu() {
		draw(screens["hostScreen"]);
	}
	void Window::drawSettingsMenu() {
		draw(screens["settingsScreen"]);
	}
	void Window::drawGame()	{
		screens["gameScreen"]->update();
		draw(screens["gameScreen"]);
	}

	//////////////////////////////////
	/// Draw the screen to the window.
	/// \param screen - the screen to be drawn.
	//////////////////////////////////
	void Window::draw(Screen* screen) {
		window->clear();
		window->draw(*screen);
		window->display();
	}

	sf::RenderWindow* Window::getRenderWindow() {
		return window;
	}

	Screen* Window::getScreen(std::string string) {
		return screens[string];
	}

	Window::~Window()
	{
		//dtor
	}
}
