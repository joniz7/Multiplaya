#ifndef HOST_GAME_SCREEN_H
#define HOST_GAME_SCREEN_H

#include "Screen.h"
#include "../guielements/Button.h"
#include "../guielements/TextField.h"
#include <map>

namespace mp
{
	class HostGameScreen : public Screen
	{
		public: 
			HostGameScreen(const sf::Vector2u &resolution);
			virtual ~HostGameScreen();

			virtual void update() {}

			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

		private:
			sf::Font* font;
			sf::Shape* background;

			sf::Text* gravityTitleText;
			sf::Text* portTitleText;
			

			sf::Text* screenTitleText;
			sf::Text* ipTitleText;

			void initBackground(const sf::Vector2u &resolution);
			void initText();
			void initFont();
			void initTextFields();
			void initButtons();

			
	};
}
#endif
