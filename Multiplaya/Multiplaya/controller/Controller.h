#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "../view/Window.h"
#include "MainScreenController.h"
#include "PauseScreenController.h"
#include "HostGameController.h"
#include "JoinGameController.h"
#include "GameController.h"
#include "../services/confighandler.h"
#include "../services/MusicHandler.h"
#include "../util/Observer.h"
#include "../model/world.h"

namespace mp
{
	/**
	 * The game's controller, handles everything except the network.
	 */
	class Controller : public Observer
	{
		public:
			Controller(World* world, Window* window);
			virtual ~Controller();
			void notify(Event e, void* object); // Observer-stuff
			void exec();
			void setNetworkHandler(NetworkHandler* network);
		protected:
		private:
			IController* currentController;		  ///< Pointer to our active controller.
			void (Window::*currentDrawFunction)();///< Pointer to our active screen.
			bool runGame; ///< Should we run the game simulation?
			std::map<std::string, IController*> controllers;
			World* world;
			Window* window;
			sf::RenderWindow* renderWindow;
		
			void startGame();
			void stopGame();
			void exitGame();
			void pauseGame();
			void resumeGame();
			void showMainMenu();
			void showJoinMenu();
			void showHostMenu();
			void showSettingsMenu();

	};
}
#endif // CONTROLLER_H

