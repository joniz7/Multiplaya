#ifndef MAINSCREENCONTROLLER_H
#define MAINSCREENCONTROLLER_H

#include "IController.h"
#include "../view/MainScreen.h"
#include <iostream>

namespace mp
{
	class MainScreenController : public IController
	{
		public:
			MainScreenController(sf::RenderWindow* window, Screen* mainScreen);
			virtual ~MainScreenController();
			void handleInput(sf::Event &event);
		protected:
		private:
		GUIElement* joinButton;

	};
}

#endif // MAINSCREENCONTROLLER_H
