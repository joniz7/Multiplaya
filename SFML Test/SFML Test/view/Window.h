#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "MainScreen.h"
#include "JoinGameScreen.h"
#include "SettingsScreen.h"
#include "HostGameScreen.h"
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

			void draw(Screen* screen);
			void drawMainMenu();
			void drawInGame();
			void drawInGameMenu();
			void drawJoinMenu();
			void drawHostMenu();
			void drawGame();
			void drawSettingsMenu();


			Screen* getScreen(std::string string);
			sf::RenderWindow* getRenderWindow();

			WorldView* getGameWindow() { return (WorldView*) screens["gameScreen"]; }
		protected:
		private:
			sf::RenderWindow* window;
		   // std::vector<Screen*> screens;
			std::map<std::string, Screen*> screens;
			WorldView* worldView;
	};
}
#endif // WINDOW_H
