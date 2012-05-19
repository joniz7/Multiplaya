#ifndef WINDOW_H
#define WINDOW_H

#include "../GameState.h"
#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "MainScreen.h"
#include "JoinGameScreen.h"
#include "SettingsScreen.h"
#include "worldview.h"
#include "../model/worlddata.h"

namespace mp
{
	class Screen;
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
			WorldView* worldView;
	};
}
#endif // WINDOW_H
