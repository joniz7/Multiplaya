#ifndef JOIN_GAME_SCREEN_H
#define JOIN_GAME_SCREEN_H

#include "Screen.h"
#include "GUIElements/Button.h"
#include "GUIElements/TextField.h"
#include <map>

namespace mp
{
	class JoinGameScreen : public Screen
	{
		public:
			JoinGameScreen(const sf::Vector2u &resolution);
			virtual ~JoinGameScreen();

			virtual void update() {}

			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
		protected:
		private:
			sf::Font* font;
			sf::Shape* background;

			sf::Text* screenTitleText;
			sf::Text* ipTitleText;
			sf::Text* portTitleText;


			
	};
}
#endif // JOIN_GAME_SCREEN_H
