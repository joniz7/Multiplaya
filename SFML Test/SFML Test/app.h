////////////////////////////////////////////////////////////
/// Application class. Manages the program, the controller,
/// if you so will.
////////////////////////////////////////////////////////////

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

// Other headers
#include <iostream>
#include <string>
#include <map>
#include <list>

// SFML specific headers
#include "sfml.h"
#include "game.h"

typedef std::list<sf::Drawable*> RenderList;

namespace mp
{
    class App
    {
        public:
            App(sf::VideoMode mode);
            ~App();
            int exec(); //Main game loop
        private:
			sf::VideoMode videoMode;
            RenderList rListObjects; //I like turtles
			WorldView * view;
			World * model;

    };
}

#endif
