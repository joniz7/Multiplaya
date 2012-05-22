#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "Screen.h"
#include <map>
#include "../services/resourcehandler.h"
#include "GUIElements/Button.h"
#include "GUIElements/TextField.h"

namespace mp
{
	class MainScreen : public Screen
	{
		public:
			MainScreen(const sf::Vector2u &resolution);
			virtual ~MainScreen();

			virtual void update() {}


			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
		protected:
		private:
			sf::Font* font;

			sf::Texture* backgroundTexture;
			sf::Sprite* backgroundSprite;

			//float calcBackgroundXScaling();

			sf::Text* gameTitleText;

			

	};

}
#endif // MAINSCREEN_H
