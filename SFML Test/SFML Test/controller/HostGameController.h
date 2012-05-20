#ifndef HOSTGAMECONTROLLER_H
#define HOSTGAMECONTROLLER_H

#include "IController.h"
#include "../view/HostGameScreen.h"

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
						
			bool gravityTextClicked;
			bool portTextClicked;


			GUIElement* cancelButton;
			GUIElement* hostButton;

			GUIElement* gravityTextField;
			GUIElement* portTextField;

			bool isNumber(sf::Event &ev);
			bool isBackspace(sf::Event &ev);
			bool isDot(sf::Event &ev);
			void removeLastCharacter(GUIElement* element);
						

	};
}

#endif // HOSTGAMECONTROLLER_H