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

		sf::Int8 packetType;
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


			if(!(receivedData >> packetType))
				std::cout<<"Error reading data from packet"<<std::endl;
			else 
			{
				switch(packetType)
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

	void NetworkHandler::sendMessage()
	{
		sf::Packet message;
		std::string mess = "Bullet fired";
		sf::Int8 ms = 1;
		message << ms << mess;

		sender.send(message, "85.226.173.155", 55001);
	}

	void NetworkHandler::notify(std::string e, void* object)
	{
		if(e == "bulletAdded")
			sendMessage();
	}

}