#ifndef TEXT_EVENT_HELPER_H
#define TEXT_EVENT_HELPER_H

#include <SFML/Window.hpp>

namespace mp 
{	
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
	};
}
#endif