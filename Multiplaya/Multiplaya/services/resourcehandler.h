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
#include <iostream>
#include <map>

// SFML specific headers
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "confighandler.h"

namespace mp
{
    class ResourceHandler
    {
        public:
			static ResourceHandler& instance();
			bool loadTexture(std::string filePath);
			void loadTextures(std::vector<std::string> pathVec);
			sf::Texture* getTexture(std::string filePath);
			bool reloadTexture(std::string filePath);
			void reloadAllTextures();

			bool loadSound(std::string filePath);
			void loadSounds(std::vector<std::string> pathVec);
			sf::SoundBuffer* getSound(std::string filePath);
			bool reloadSound(std::string filePath);
			void reloadAllSounds();

			void doRealTimeLoading(bool b){doRtLoading=b;};
        private:
			ResourceHandler();
			ResourceHandler(ResourceHandler const&){};
			ResourceHandler& operator=(ResourceHandler const&);

			std::map<std::string, sf::Texture> texMap;
			std::map<std::string, sf::SoundBuffer> soundMap;
			bool doRtLoading;
    };
}

#endif
