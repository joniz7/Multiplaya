#ifndef HOSTGAMECONTROLLER_H
#define HOSTGAMECONTROLLER_H

#include "IController.h"
#include "../view/screens/HostGameScreen.h"
#include "../util/TextEventHelper.h"
#include "../services/networkhandler.h"

namespace mp
{
	// Forward declaration.
	class NetworkHandler;

	/**
	 * Controls the "Host game" screen.
	 */
	class HostGameController : public IController
	{
		public:
			HostGameController(sf::RenderWindow* window, Screen* hostScreen);
			virtual ~HostGameController();
			void handleInput();
			/// Sets which NetworkHandler "host game" should use.
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