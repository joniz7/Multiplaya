#ifndef WINDOW_H
#define WINDOW_H

#include "../GameState.h"

#include "Screen.h"
#include "MainScreen.h"
#include "JoinGameScreen.h"
#include "SettingsScreen.h"
#include "worldview.h"
#include "../model/worlddata.h"

namespace mp
{
	class Window
	{
		public:
			Window(WorldData* worldData);
			virtual ~Window();
			void exec();

			Screen* getScreen(std::string string);
			sf::RenderWindow* getRenderWindow();

			WorldView* getGameWindow() { return (WorldView*) screens["hostScreen"]; }
		protected:
		private:
			sf::RenderWindow* window;
		   // std::vector<Screen*> screens;
		   std::map<std::string, Screen*> screens;
	};
}
#endif // WINDOW_H
