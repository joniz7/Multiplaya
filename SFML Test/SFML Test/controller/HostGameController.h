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
			void handleInput(sf::Event &event);
		protected:
		private:

	};
}

#endif // HOSTGAMECONTROLLER_H