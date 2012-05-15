#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "../GameState.h"
#include "../view/Window.h"
#include "MainScreenController.h"
#include "HostGameController.h"
#include "JoinGameController.h"
#include "GameController.h"
#include "../model/world.h"

namespace mp
{
	class Controller
	{
		public:
			Controller(World* world, Window* window);
			virtual ~Controller();
			void exec();
			void setNetworkHandler(NetworkHandler* network);
		protected:
		private:
			//alternative is a map
			sf::Event* event;
			//std::vector<IController*> controllers;
			std::map<std::string, IController*> controllers;
			Window* window;
			sf::RenderWindow* renderWindow;

			// sf window reference
	};
}
#endif // CONTROLLER_H
