#include "HostGameController.h"

namespace mp
{
	HostGameController::HostGameController(sf::RenderWindow* window, Screen* hostScreen) : IController(window, hostScreen)
	{
		//ctor
	}

	HostGameController::~HostGameController()
	{
		//dtor
	}

	void HostGameController::handleInput()
	{
		while (getRenderWindow()->pollEvent(ev))
		{

		}

	}
}