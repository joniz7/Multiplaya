#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "Screen.h"
#include <map>
#include "../../services/resourcehandler.h"
#include "../GUIElements/Button.h"
#include "../GUIElements/TextField.h"

namespace mp
{
	class PauseScreen : public Screen
	{
		public:
			PauseScreen(const sf::Vector2u &resolution);
			virtual ~PauseScreen();

			virtual void update() {}
			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
		protected:
		private:
			sf::Font* font;

			sf::Texture* backgroundTexture;
			sf::Sprite* backgroundSprite;

			//float calcBackgroundXScaling();
			sf::Texture* getRandomBackground();
			void initBackground(const sf::Vector2u &resolution);
			void initFont();
			void initText();
			void initButtons();

			sf::Text* gameTitleText;
			sf::Text* gameSubtitleText;
	};

}
#endif // MAINSCREEN_H
