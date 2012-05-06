////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "networkhandler.h"

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

		currentClientID = 1;

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

		running = true;

		Client client;
		std::string name;
		////////////////////////////////////////////////////////////
		// Main loop of network handler.
		// Constantly checks if there are any incoming data packets
		////////////////////////////////////////////////////////////
		while(running) 
		{
			//Receives a packet
			std::cout<<"Receiving data..."<<std::endl;
			receiver.receive(receivedData, senderIP, senderPort);

			//Tries to read what type of message the packet was
			if(!(receivedData >> type))
				std::cout<<"Error reading data from packet"<<std::endl;
			else 
			{
				switch(type)
				{
					//Client trying to connect
					case 1:
						//Creates a client from the data

						receivedData >> name;
	
						client.IP = senderIP;
						client.port = senderPort;
						client.name = name;

						//adds that client to the clientmap
						clientMap[1] = client;

						break;
					//Receive a text message
					case 2:

						std::string message;
						receivedData >> message;
						std::cout<<"Recieved a message: "<<message<<std::endl;

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

	////////////////////////////////////////////////////////////
	// Sends a message over the internet
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendMessage(std::string message)
	{
		sf::Packet packet;

		sf::Int8 type = 2;
		packet << type << message;

		sender.send(packet, "85.226.173.163", 55001);
	}

	////////////////////////////////////////////////////////////
	// Puts the character in a packet and sends it.
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendCharacterPos(int index)
	{
		/*
		Character* character = worldData->getCharacter(index);

		b2Vec2 vector = character->getBody()->GetPosition();

		float32 x = vector.x;
		float32 y = vector.y;

		std::string s;
		std::stringstream out;
		out << "hej";
		s = out.str();

		sendMessage(s);
		*/
	}

	void NetworkHandler::notify(std::string e, void* object)
	{
			sendMessage(e);
	}
}

