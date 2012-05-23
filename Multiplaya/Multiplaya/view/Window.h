#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

#include "screens/MainScreen.h"
#include "screens/PauseScreen.h"
#include "screens/JoinGameScreen.h"
#include "screens/SettingsScreen.h"
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

			void drawMainMenu();
			void drawPauseMenu();
			void drawJoinMenu();
			void drawGame();
			void drawSettingsMenu();

			Screen* getScreen(std::string string);
			sf::RenderWindow* getRenderWindow();

			/// Returns the gamewindow / screen
			WorldView* getGameWindow() { return static_cast<WorldView*>(screens["gameScreen"]); }
		protected:
		private:
			sf::RenderWindow* window;
			std::map<std::string, Screen*> screens;
			WorldView* worldView;

			void draw(Screen* screen);

			void initRenderWindow(const std::string screenTitle);
			void initScreens(WorldData* worldData);
	};
}
#endif // WINDOW_H
