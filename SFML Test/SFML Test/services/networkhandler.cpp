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
    NetworkHandler::NetworkHandler( )
    {
		//Binds the receiving socket to port 4567
		if(!receiver.bind(4567))
			std::cout<<"Error binding to port 4567"<<std::endl;
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
			receiver.receive(receivedData, senderIP, senderPort);

			if(!(receivedData >> packetType))
				std::cout<<"Error reading data from packet"<<std::endl;
			else 
			{
				switch(packetType)
				{
					case 1:
						receivedData >> message;
						std::cout<<message<<std::endl;
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
}