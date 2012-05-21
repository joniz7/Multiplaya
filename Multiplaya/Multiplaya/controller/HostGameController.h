#ifndef HOSTGAMECONTROLLER_H
#define HOSTGAMECONTROLLER_H

#include "IController.h"
#include "../view/HostGameScreen.h"
#include "../util/TextEventHelper.h"

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
						
			bool gravityTextClicked;
			bool portTextClicked;

			GUIElement* cancelButton;
			GUIElement* hostButton;

			GUIElement* gravityTextField;
			GUIElement* portTextField;

			NetworkHandler* networkHandler;
						

	};
}

#endif // HOSTGAMECONTROLLER_H