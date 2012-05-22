#ifndef PAUSESCREENCONTROLLER_H
#define PAUSESCREENCONTROLLER_H

#include "IController.h"
#include "../view/screens/PauseScreen.h"
#include <iostream>

namespace mp
{
	/**
	 * Controls the pause menu.
	 */
	class PauseScreenController : public IController
	{
		public:
			PauseScreenController(sf::RenderWindow* window, Screen* mainScreen);
			virtual ~PauseScreenController();
			void handleInput();
		protected:
		private:
		sf::Event ev;
		GUIElement* resumeButton;
		GUIElement* disconnectButton;
		GUIElement* exitButton;
	};
}

#endif // MAINSCREENCONTROLLER_H
