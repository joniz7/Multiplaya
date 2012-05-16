#ifndef HOSTGAMECONTROLLER_H
#define HOSTGAMECONTROLLER_H

#include "IController.h"

namespace mp
{
	class HostGameController : public IController
	{
		public:
			HostGameController(sf::RenderWindow* window, Screen* hostScreen);
			virtual ~HostGameController();
			void handleInput();
		protected:
		private:
			sf::Event ev;

	};
}

#endif // HOSTGAMECONTROLLER_H