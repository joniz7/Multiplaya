////////////////////////////////////////////////////////////
/// Class description
////////////////////////////////////////////////////////////
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include <iostream>

// SFML specific headers
#include <SFML/Window.hpp>

// Box2D specific headers
#include <Box2D.h>

#include "confighandler.h"
#include "keylookup.h"

namespace mp
{
	/**
	 * A class which keeps track of input, and more specifically
	 * which keys are bound to which actions. Reads the key config
	 * from the configuration file.
	 */
    class Input
    {
        public:
			Input();
            ~Input();

			/// Returns true if player is holding down the button associated with left, false otherwise.
			bool btnDwnLeft()		{ return sf::Keyboard::isKeyPressed( btnLeft ); }
			/// Returns true if player is holding down the button associated with right, false otherwise.
			bool btnDwnRight()		{ return sf::Keyboard::isKeyPressed( btnRight ); }
			/// Returns true if player is holding down the button associated with up, false otherwise.
			bool btnDwnUp()			{ return sf::Keyboard::isKeyPressed( btnUp ); }
			/// Returns true if player is holding down the button associated with down, false otherwise.
			bool btnDwnDown()		{ return sf::Keyboard::isKeyPressed( btnDown ); }
			/// Returns true if player is holding down the button associated with jump, false otherwise.
			bool btnDwnJump()		{ return sf::Keyboard::isKeyPressed( btnJump ); }
			/// Returns true if player is holding down the button associated with primary fire, false otherwise.
			bool btnDwnPrimary()	{ return sf::Mouse::isButtonPressed( btnPrimary ); }
			/// Returns true if player is holding down the button associated with secondary fire, false otherwise.
			bool btnDwnSecondary()	{ return sf::Mouse::isButtonPressed( btnSecondary ); }
			/// Returns true if player is holding down the button associated with reloading, false otherwise.
			bool btnDwnReload()		{ return sf::Keyboard::isKeyPressed( btnReload ); }

        private:
			sf::Keyboard::Key btnLeft;
			sf::Keyboard::Key btnRight;
			sf::Keyboard::Key btnUp;
			sf::Keyboard::Key btnDown;
			sf::Keyboard::Key btnJump;
			sf::Mouse::Button btnPrimary;
			sf::Mouse::Button btnSecondary;
			sf::Keyboard::Key btnReload;

			KeyLookup* keyLib;
			
    };
}

#endif
