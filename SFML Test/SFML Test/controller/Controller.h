#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "../view/Window.h"
#include "MainScreenController.h"
#include "HostGameController.h"
#include "JoinGameController.h"
#include "GameController.h"
#include "../services/confighandler.h"
#include "../services/MusicHandler.h"
#include "../util/Observer.h"
#include "../util/Event.h"
#include "../model/world.h"

namespace mp
{
	class Controller : public Observer
	{
		// The different states the game can be in.
		enum State {
			MAIN_MENU,
			JOIN_MENU,
			HOST_MENU,
			SETTINGS_MENU,
			INGAME,
			INGAME_MENU
		};


		public:
			Controller(World* world, Window* window);
			virtual ~Controller();
			void notify(Event e, void* object); // Observer-stuff
			void exec();
			void setNetworkHandler(NetworkHandler* network);
		protected:
		private:
			State state;
			bool runGame;
			std::map<std::string, IController*> controllers;
			World* world;
			Window* window;
			sf::RenderWindow* renderWindow;

	};
}
#endif // CONTROLLER_H

