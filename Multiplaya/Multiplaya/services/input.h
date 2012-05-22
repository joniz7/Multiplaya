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
    class Input
    {
        public:
			Input();
            ~Input();

			bool btnDwnLeft()		{ return sf::Keyboard::isKeyPressed( btnLeft ); }
			bool btnDwnRight()		{ return sf::Keyboard::isKeyPressed( btnRight ); }
			bool btnDwnUp()			{ return sf::Keyboard::isKeyPressed( btnUp ); }
			bool btnDwnDown()		{ return sf::Keyboard::isKeyPressed( btnDown ); }
			bool btnDwnJump()		{ return sf::Keyboard::isKeyPressed( btnJump ); }
			bool btnDwnPrimary()	{ return sf::Mouse::isButtonPressed( btnPrimary ); }
			bool btnDwnSecondary()	{ return sf::Mouse::isButtonPressed( btnSecondary ); }
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
