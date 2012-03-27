/*
/ Rendering window class
/ Author: Felix Willebrand Westin
/ File created: 2012-03-16
/ File updated: 2012-03-16
/ License: GPLv3
*/
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <list>

#include <SFML/Graphics.hpp>

typedef std::list<sf::Drawable*> RenderList;

namespace mp
{
    class Window : public sf::RenderWindow
    {
        /*
        The Window class is an extension of the default RenderWindow class that acts as the container for the rest of the game.
        */
        public:
            Window(sf::VideoMode mode, std::string title);
            ~Window();
            int exec(); //Main game loop
        private:
            RenderList rListObjects;
    };
}

#endif
