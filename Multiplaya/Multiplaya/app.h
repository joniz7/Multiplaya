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

#include "model/worlddata.h"
#include "controller/Controller.h"
#include "view/Window.h"
#include "services/resourcehandler.h"

typedef std::list<sf::Drawable*> RenderList;

namespace mp
{
	/**
	 * The application class.
	 * Creates the main parts of the application, and launches 
	 * both the game and the NetworkHandler in different threads.
	 * Contains the main loop of the program.
	 */
	class App
    {
        public:
           // App(sf::VideoMode mode);
			App() {};
			~App(){};
            int exec();
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
