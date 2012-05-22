#include "IController.h"

namespace mp
{
	/**
	 * Creates a new controller.
	 * Saves the supplied RenderWindow and Screen in member variables.
	 */
	IController::IController(sf::RenderWindow* window, Screen* screen)
	{
		this->window = window,
		this->screen = screen;
	}

	IController::~IController() {}

	/**
	 * Getter for the RenderWindow associated with the controller.
	 * @return the associated RenderWindow.
	 */
	sf::RenderWindow* IController::getRenderWindow()
	{
		return window;
	}


	/**
	 * Getter for the Screen associated with the controller.
	 * @return the associated Screen.
	 */
	Screen* IController::getScreen()
	{
		return screen;
	}
}