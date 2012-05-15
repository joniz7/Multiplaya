#ifndef JOINGAMECONTROLLER_H
#define JOINGAMECONTROLLER_H

#include "IController.h"
#include "../view/JoinGameScreen.h"
#include <iostream>

namespace mp
{
	class JoinGameController : public IController
	{
		public:
			JoinGameController(sf::RenderWindow* window, Screen* joinGameScreen);
			virtual ~JoinGameController();
			void handleInput(sf::Event &ev);
		protected:
		private:

			bool ipTextClicked;
			bool portTextClicked;

			bool isNumberOrDot(sf::Event &ev);

			GUIElement* cancelButton;
			GUIElement* connectButton;

			GUIElement* ipTextField;
			GUIElement* portTextField;

	};
}

#endif // JOINGAMECONTROLLER_H
