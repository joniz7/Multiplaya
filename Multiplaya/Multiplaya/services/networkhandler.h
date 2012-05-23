////////////////////////////////////////////////////////////
/// Network handler. Handles networking
////////////////////////////////////////////////////////////
#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <cmath>
#include <map>
#include <iostream>

// SFML specific headers
#include <SFML/Network.hpp>

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../global.h"
#include "../client.h"
#include "../model/world.h"
#include "../model/worlddata.h"

namespace mp
{
	class World;
    class NetworkHandler : public Observer
    {
        public:
			NetworkHandler(WorldData* worldData, World* model);
			void exec();
            ~NetworkHandler();
			void sendMessage(std::string messages, sf::IpAddress IP);
			void sendMessageToServer(std::string message);
			void sendMessageToEveryone(std::string message);
			void sendClientID(sf::Int8 ID);
			void connectToServer(std::string name);
			void connectToServer(std::string name, std::string IPAddress);
			void disconnectClient(sf::Int8 clientID);
			bool isConnectedToServer(){return hasConnected;};
			void sendCharacterDataToServer();
			void sendCharacterDataToClient(sf::Int8 clientID);
			void sendCharactersToClient(sf::Int8 clientID);
			void sendBulletDataToServer();
			void sendBulletDataToClient(sf::Int8 clientID);
			void removeCharacter(sf::Int8 clientID);
			void updateAllClients();
			void setIPAddress(const sf::String IPAddress);
			void setAsServer();
			void setAsClient();

			bool isServer, isClient;

			virtual void notify(Event e, void* object);
        private:
			
			void setCharacterData(sf::Int8 clientID, b2Vec2 position, b2Vec2 velocity, float32 angle, bool grounded, bool walking, bool facingLeft, bool touchingLeftWall, bool touchingRightWall, bool wallSliding, bool flipping);
			sf::UdpSocket receiver;
			sf::UdpSocket sender;
			bool running;
			WorldData* worldData;
			World* model;
			std::map<sf::Int8, Client> clientMap;
			sf::Int8 currentClientID;
			sf::IpAddress serverIP;
			unsigned short receivePort;
			sf::Int8 myID;
			bool hasConnected;
			std::vector<BufferBullet> bulletsToSend;

			bool sendOutput;
    };
}

#endif

