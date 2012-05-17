#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "../view/Window.h"
#include "MainScreenController.h"
#include "HostGameController.h"
#include "JoinGameController.h"
#include "GameController.h"
#include "../services/confighandler.h"
#include "../services/musichandler.h"
#include "../model/world.h"

namespace mp
{
	class Controller
	{
		public:
			Controller(World* world, Window* window);
			virtual ~Controller();
			void exec();
			void initTitleMusic();
			void setNetworkHandler(NetworkHandler* network);
		protected:
		private:
			//std::vector<IController*> controllers;
			std::map<std::string, IController*> controllers;
			Window* window;
			sf::RenderWindow* renderWindow;
			sf::Music* titleMusic;

			// sf window reference
	};
}
#endif // CONTROLLER_H
