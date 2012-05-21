#ifndef TEXT_EVENT_HELPER_H
#define TEXT_EVENT_HELPER_H

#include "../view/GUIElements/GUIElement.h"

namespace mp 
{
	// maybe change name to controller helper
	class TextEventHelper
	{
		public:
			static bool isNumber(sf::Event &ev);
			static bool isBackspace(sf::Event &ev);
			static bool isDot(sf::Event &ev);
			static void removeLastCharacter(GUIElement * const element);
	};
}
#endif