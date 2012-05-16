#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "Screen.h"


namespace mp
{
	class SettingsScreen : public Screen
	{
		public:
			SettingsScreen(const sf::Vector2u &resolution);
			virtual ~SettingsScreen();

			virtual void update() {}
			bool hover(const sf::Vector2i& mousePos) { return true;}
		   // int click(const sf::Vector2i& mousePos) { return 0; }
			virtual GUIElement* getElement(std::string element) { return buttons[element]; }
		protected:
		private:
			std::map<std::string, GUIElement*> buttons;
			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
	};

}
#endif // SETTINGSSCREEN_H
