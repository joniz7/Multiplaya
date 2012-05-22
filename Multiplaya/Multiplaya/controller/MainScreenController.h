#ifndef MAINSCREENCONTROLLER_H
#define MAINSCREENCONTROLLER_H

#include "IController.h"
#include "../view/screens/MainScreen.h"
#include <iostream>

namespace mp
{
	/**
	 * Controls the main menu.
	 */
	class MainScreenController : public IController
	{
		public:
			MainScreenController(sf::RenderWindow* window, Screen* mainScreen);
			virtual ~MainScreenController();
			void handleInput();
		protected:
		private:
		sf::Event ev;
		GUIElement* joinButton;
		GUIElement* hostButton;
		GUIElement* exitButton;
	};
}

#endif // MAINSCREENCONTROLLER_H
