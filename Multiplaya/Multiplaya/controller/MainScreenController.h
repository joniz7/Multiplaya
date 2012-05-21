#ifndef MAINSCREENCONTROLLER_H
#define MAINSCREENCONTROLLER_H

#include "IController.h"
#include "../view/MainScreen.h"
#include "../services/networkhandler.h"
#include <iostream>

namespace mp
{
	class MainScreenController : public IController
	{
		public:
			MainScreenController(sf::RenderWindow* window, Screen* mainScreen);
			virtual ~MainScreenController();
			void handleInput();
			void setNetworkHandler(NetworkHandler* network){networkHandler = network;};
		protected:
		private:
		sf::Event ev;
		GUIElement* joinButton;
		GUIElement* hostButton;
		GUIElement* exitButton;

		NetworkHandler* networkHandler;

	};
}

#endif // MAINSCREENCONTROLLER_H
