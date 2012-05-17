#ifndef JOINGAMESCREEN_H
#define JOINGAMESCREEN_H

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

			virtual bool hover(const sf::Vector2i& mousePos);

			virtual void update() {}
		   // int click(const sf::Vector2i& mousePos) { return 1; };
			virtual GUIElement* getElement(std::string element);
		protected:
		private:
			sf::Font* font;
			sf::Shape* background;
			Button* connectButton;
			Button* cancelButton;
			std::map<std::string, GUIElement*> guiElements;

			sf::Text* screenTitleText;
			sf::Text* ipTitleText;
			sf::Text* portTitleText;

			TextField* ipTextField;
			TextField* portTextField;



			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
	};
}
#endif // JOINGAMESCREEN_H
