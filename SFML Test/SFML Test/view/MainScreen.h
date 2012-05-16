#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "Screen.h"
#include "GUIElements/Button.h"
#include "GUIElements/TextField.h"
#include <map>

namespace mp
{
	class MainScreen : public Screen
	{
		public:
			MainScreen(const sf::Vector2u &resolution);
			virtual ~MainScreen();

			virtual bool hover(const sf::Vector2i& mousePos);
			//int click(const sf::Vector2i& mousePos);
			virtual GUIElement* getElement(std::string element);

			virtual void update() {}
		protected:
		private:
			sf::Font* font;

			sf::Texture* backgroundTexture;
			sf::Sprite* backgroundSprite;

			//float calcBackgroundXScaling();

			sf::Text* gameTitleText;

			std::map<std::string, Button*> buttons;

			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	};

}
#endif // MAINSCREEN_H