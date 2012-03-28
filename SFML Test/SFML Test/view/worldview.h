////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////
#ifndef WORLDVIEW_H_INCLUDED
#define WORLDVIEW_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include "../sfml.h"

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../game.h"

namespace mp
{
    class WorldView
    {
        public:
			WorldView();
			void exec();
			sf::RenderWindow* getWindow();
			sf::View* getView();
            ~WorldView();
			
		protected:
    		
		private:
			sf::RenderWindow* window;
			sf::View* view;
    };
}

#endif