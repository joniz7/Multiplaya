#ifndef JOINGAMECONTROLLER_H
#define JOINGAMECONTROLLER_H

#include "IController.h"
#include "../view/JoinGameScreen.h"
#include "../services/networkhandler.h"
#include <iostream>

namespace mp
{
	class JoinGameController : public IController
	{
		public:
			JoinGameController(sf::RenderWindow* window, Screen* joinGameScreen);
			virtual ~JoinGameController();
			void handleInput();
			void setNetworkHandler(NetworkHandler* network){networkHandler = network;};
		protected:
		private:
			sf::Event ev;

			bool ipTextClicked;
			bool portTextClicked;

			bool isNumber(sf::Event &ev);
			bool isDot(sf::Event &ev);
			bool isBackspace(sf::Event &ev);

			void removeLastCharacter(GUIElement* element);

			GUIElement* cancelButton;
			GUIElement* connectButton;

			GUIElement* ipTextField;
			GUIElement* portTextField;

			NetworkHandler* networkHandler;

	};
}

#endif // JOINGAMECONTROLLER_H
