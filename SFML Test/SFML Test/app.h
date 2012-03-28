////////////////////////////////////////////////////////////
/// Application class. Manages the program, the controller,
/// if you so will.
////////////////////////////////////////////////////////////
#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <list>

#include <SFML/Graphics.hpp>

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
            RenderList rListObjects;
    };
}

#endif
