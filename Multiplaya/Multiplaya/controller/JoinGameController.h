#ifndef JOINGAMECONTROLLER_H
#define JOINGAMECONTROLLER_H

#include "IController.h"
#include "../view/screens/JoinGameScreen.h"
#include "../services/networkhandler.h"
#include "../util/TextEventHelper.h"
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

			GUIElement* cancelButton;
			GUIElement* connectButton;

			TextField* ipTextField;
			TextField* portTextField;

			NetworkHandler* networkHandler;

			sf::Clock clock;

	};
}

#endif // JOINGAMECONTROLLER_H
