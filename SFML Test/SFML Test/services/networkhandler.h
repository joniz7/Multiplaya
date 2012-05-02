////////////////////////////////////////////////////////////
/// Network handler. Handles networking
////////////////////////////////////////////////////////////
#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "game.h"

//#include "textmessage.h"

namespace mp
{
    class NetworkHandler : public Observer
    {
        public:
			NetworkHandler(WorldData* worldData);
			void exec();
            ~NetworkHandler();
			void sendMessage(std::string message);
			virtual void notify(std::string e, void* object);
        private:
			sf::UdpSocket receiver;
			sf::UdpSocket sender;
			bool running;
			WorldData* worldData;
			
    };



}

#endif

