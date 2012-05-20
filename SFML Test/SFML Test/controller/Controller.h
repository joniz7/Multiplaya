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
#include "../model/world.h"

namespace mp
{					// TODO implement observers?
	class Controller// : public Observer
	{

		public:
			Controller(World* world, Window* window);
			virtual ~Controller();
			// TODO implement observers?
			//void notify(Event e, void* object); // Observer-stuff
			void exec();
			void setNetworkHandler(NetworkHandler* network);
		protected:
		private:
			bool inGame;
			std::map<std::string, IController*> controllers;
			World* world;
			Window* window;
			sf::RenderWindow* renderWindow;
			sf::Music* titleMusic;

	};
}
#endif // CONTROLLER_H

