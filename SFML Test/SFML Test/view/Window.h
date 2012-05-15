#ifndef WINDOW_H
#define WINDOW_H

#include "../GameState.h"

#include "Screen.h"
#include "MainScreen.h"
#include "JoinGameScreen.h"
#include "SettingsScreen.h"
#include "worldview.h"

namespace mp
{
	class Window
	{
		public:
			Window();
			virtual ~Window();
			void run();

			Screen* getScreen(std::string string);
			sf::RenderWindow* getRenderWindow();
		protected:
		private:
			sf::RenderWindow* window;
		   // std::vector<Screen*> screens;
		   std::map<std::string, Screen*> screens;
	};
}
#endif // WINDOW_H
