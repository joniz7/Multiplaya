#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <sfml/Graphics.hpp>
#include "GameState.h"

namespace mp
{
	class Screen;

	class IController
	{
		public:
			 IController(sf::RenderWindow* window, Screen* screen);
			 virtual ~IController();
			// might be a better way to send window in constructor instead
			virtual void handleInput() = 0;

			Screen* getScreen();
			sf::RenderWindow* getRenderWindow();
		protected:
		private:
			sf::RenderWindow* window;
			Screen* screen;

	};
}
#endif // ICONTROLLER_H
