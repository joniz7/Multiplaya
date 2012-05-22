#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <SFML/Graphics.hpp>
#include "../util/Observable.h"

namespace mp
{
	class Screen;

	/**
	 * A controller interface, which all controllers implements.
	 */
	class IController : public Observable
	{
		public:
			IController(sf::RenderWindow* window, Screen* screen);
			virtual ~IController();

			/// method which is supposed to handle events from renderwindow
			virtual void handleInput() = 0;

			/// returns pointer to screen
			Screen* getScreen();
			/// returns pointer to renderwindow
			sf::RenderWindow* getRenderWindow();
		protected:
		private:
			sf::RenderWindow* window;
			Screen* screen;

	};
}
#endif // ICONTROLLER_H
