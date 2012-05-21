#ifndef HOST_GAME_SCREEN_H
#define HOST_GAME_SCREEN_H

#include "Screen.h"
#include "GUIElements/Button.h"
#include "GUIElements/TextField.h"
#include <map>

namespace mp
{
	class HostGameScreen : public Screen
	{
		public: 
			HostGameScreen(const sf::Vector2u &resolution);
			virtual ~HostGameScreen();

			virtual bool hover(const sf::Vector2i& mousePos);

			virtual void update() {}

			virtual GUIElement* getElement(std::string element);

		private:
			sf::Font* font;
			sf::Shape* background;

			Button* hostButton;
			Button* cancelButton;

			std::map<std::string, GUIElement*> guiElements;

			sf::Text* gravityTitleText;
			sf::Text* portTitleText;
			

			sf::Text* screenTitleText;
			sf::Text* ipTitleText;

			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
	};
}
#endif
