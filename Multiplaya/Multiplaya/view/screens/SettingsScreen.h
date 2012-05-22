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
			void hover(const sf::Vector2i& mousePos) { }
			
			virtual GUIElement* getElement(std::string element) { return guiElements[element]; }

			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
		protected:
		private:
			std::map<std::string, GUIElement*> guiElements;
			
	};

}
#endif // SETTINGSSCREEN_H
