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
#include <map>
#include <iostream>

// SFML specific headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../game.h"
#include "../client.h"

namespace mp
{
    class NetworkHandler : public Observer
    {
        public:
			NetworkHandler(WorldData* worldData);
			void exec();
            ~NetworkHandler();
			void sendMessage(std::string messages, sf::IpAddress IP);
			void sendMessageToServer(std::string message);
			void sendMessageToEveryone(std::string message);

			void connectToServer(std::string name);

			virtual void notify(Event e, void* object);
        private:
			sf::UdpSocket receiver;
			sf::UdpSocket sender;
			bool running;
			WorldData* worldData;
			std::map<sf::Int8,Client> clientMap;
			int currentClientID;
			sf::IpAddress myIP;
			unsigned short receivePort;

			bool hasConnected;
    };
}

#endif

