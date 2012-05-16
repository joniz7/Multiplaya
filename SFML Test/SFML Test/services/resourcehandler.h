////////////////////////////////////////////////////////////
/// Class for managing loading and distribution of resources
/// such as textures, sounds etc.
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
#include "../sfml.h"

#include "confighandler.h"

namespace mp
{
    class ResourceHandler
    {
        public:
			ResourceHandler();
            ~ResourceHandler();
			bool loadTexture(std::string filePath);
			void loadTextures(std::vector<std::string> pathVec);
			sf::Texture* getTexture(std::string filePath);
			bool reloadTexture(std::string filePath);
			void reloadAllTextures();
			void doRealTimeLoading(bool b){doRtLoading=b;};
        private:
			std::map<std::string, sf::Texture> texMap;
			bool doRtLoading;
    };
}

#endif
