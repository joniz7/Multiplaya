////////////////////////////////////////////////////////////
/// Class description
////////////////////////////////////////////////////////////
#ifndef RESOURCEHANDLER_H_INCLUDED
#define RESOURCEHANDLER_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include <map>

// SFML specific headers
#include "sfml.h"

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "game.h"

//Defines
#include "defines.h"

namespace mp
{
    class ResourceHandler
    {
        public:
			ResourceHandler();
            ~ResourceHandler();
			bool loadTexture(std::string filePath);
			sf::Texture* getTexture(std::string filePath);
			void doRealTimeLoading(bool b){doRtLoading=b;};
        private:
			std::map<std::string, sf::Texture> texMap;
			bool doRtLoading;
    };
}

#endif
