////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "networkhandler.h"

#include <iostream>

////////////////////////////////////////////////////////////
/// Network handler. Handles networking
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    NetworkHandler::NetworkHandler(WorldData* worldData)
    {
		this->worldData = worldData;

		unsigned short port = 55001;
		//Binds the receiving socket to a port
		if(!receiver.bind(port))
		{
			std::cout<<"Error binding to port "<<port<<std::endl;
		}
    }

	void NetworkHandler::exec() 
	{

		//Data about sender
		sf::Packet receivedData;
		sf::IpAddress senderIP;
		unsigned short senderPort;

		sf::Int8 type;
		std::string message;

		running = true;

		////////////////////////////////////////////////////////////
		// Main loop of network handler.
		// Constantly checks if there are any incoming data packets
		////////////////////////////////////////////////////////////
		while(running) 
		{
			std::cout<<"Receiving data..."<<std::endl;
			receiver.receive(receivedData, senderIP, senderPort);


			if(!(receivedData >> type))
				std::cout<<"Error reading data from packet"<<std::endl;
			else 
			{
				switch(type)
				{
					case 1:
						receivedData >> message;
						std::cout<<"Message received: "<<message<<std::endl;
						break;
						
				}
			}
		}
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    NetworkHandler::~NetworkHandler()
    {

    }

	void NetworkHandler::sendMessage(std::string message)
	{
		sf::Packet packet;

		sf::Int8 type = 1;
		packet << type << message;

		sender.send(packet, "85.226.173.155", 55001);
	}

	void NetworkHandler::notify(std::string e, void* object)
	{
		if(e == "bulletAdded")
			sendMessage(e);
	}
}

