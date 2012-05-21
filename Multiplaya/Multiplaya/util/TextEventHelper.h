#ifndef TEXT_EVENT_HELPER_H
#define TEXT_EVENT_HELPER_H

#include "../view/GUIElements/GUIElement.h"

namespace mp 
{
	// maybe change name to controller helper
	
	/// Class for helping Controller
	class TextEventHelper
	{
		public:
			/// Checks if textevent is a number
			static bool isNumber(sf::Event &textEvent);
			/// Checks if textevent is a backspace
			static bool isBackspace(sf::Event &textEvent);
			/// Checks if textevent is a dot
			static bool isDot(sf::Event &textEvent);
			/// Removes the last character in GUIElement passed
			static void removeLastCharacter(GUIElement * const element);
	};
}
#endif