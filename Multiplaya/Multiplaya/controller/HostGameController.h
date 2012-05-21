#ifndef HOSTGAMECONTROLLER_H
#define HOSTGAMECONTROLLER_H

#include "IController.h"
#include "../view/HostGameScreen.h"
#include "../util/TextEventHelper.h"
#include "../services/networkhandler.h"

namespace mp
{
	class NetworkHandler;
	class HostGameController : public IController
	{
		public:
			HostGameController(sf::RenderWindow* window, Screen* hostScreen);
			virtual ~HostGameController();
			void handleInput();
			void setNetworkHandler(NetworkHandler* network){networkHandler = network;};
		protected:
		private:
			sf::Event ev;

			GUIElement* cancelButton;
			GUIElement* hostButton;

			TextField* gravityTextField;
			TextField* portTextField;

			NetworkHandler* networkHandler;
						

	};
}

#endif // HOSTGAMECONTROLLER_H