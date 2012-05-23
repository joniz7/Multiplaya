#ifndef TEXT_EVENT_HELPER_H
#define TEXT_EVENT_HELPER_H

#include <SFML/Window.hpp>

namespace mp 
{	
	/**
	 * A helper class for UI controllers.
	 * Provides methods for checking input easily.
	 */
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