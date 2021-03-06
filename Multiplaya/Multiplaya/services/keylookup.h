#ifndef KEYLOOKUP_H_INCLUDED
#define KEYLOOKUP_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include <map>

// SFML specific headers
#include <SFML/Window.hpp>

namespace mp
{
	/**
	 * Class for translating config key codes to SFML keys and
	 * mouse buttons.
	 */
    class KeyLookup
    {
        public:
			sf::Keyboard::Key getKey(std::string keyName);
			sf::Mouse::Button getMouseButton(std::string keyName);
    };
}

#endif
