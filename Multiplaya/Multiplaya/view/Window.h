#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

#include "screens/MainScreen.h"
#include "screens/JoinGameScreen.h"
#include "screens/SettingsScreen.h"
#include "screens/HostGameScreen.h"
#include "screens/worldview.h"

namespace mp
{
	class Screen;
	class WorldData;
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

			WorldView* getGameWindow() { return static_cast<WorldView*>(screens["gameScreen"]); }
		protected:
		private:
			sf::RenderWindow* window;
		   // std::vector<Screen*> screens;
			std::map<std::string, Screen*> screens;
			WorldView* worldView;
	};
}
#endif // WINDOW_H
