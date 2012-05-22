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
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "model/world.h"
#include "model/worlddata.h"
#include "controller/Controller.h"
#include "view/Window.h"
#include "services/resourcehandler.h"

typedef std::list<sf::Drawable*> RenderList;

namespace mp
{
    class App
    {
        public:
           // App(sf::VideoMode mode);
			App() {};
			~App(){};
            int exec(); //Main game loop
        private:
			sf::VideoMode videoMode;
            RenderList rListObjects;
			WorldData* worldData;
			WorldView* view;
			World* model;
			Controller* controller;
    };
}

#endif
