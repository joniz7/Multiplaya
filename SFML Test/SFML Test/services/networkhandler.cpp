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

		myIP = "85.226.173.176";
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

		sf::Int8 clientID;

		std::string message;

		sf::Packet packet;
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

						std::cout<<name<<" has connected with IP: "<<senderIP<<std::endl;

						break;
					//Client trying to disconnect
					case 2:
						receivedData >> clientID;

						client = clientMap[clientID];

						std::cout<<name<<" has disconnected"<<std::endl;

						clientMap.erase(clientID);
						break;

					//Receive a text message and send it to all clients
					case 3:
						message.clear();
						receivedData >> message;
						std::cout<<"Recieved a message: "<<message<<std::endl;

						type = 4;

						if(!clientMap.empty())
						{
							for(sf::Int8 i = 1; i != clientMap.size(); i++)
							{
								packet.clear();
								client = clientMap[i];

								packet<<type<<message;
								sender.send(packet, client.IP, client.port);
							}
						}

						break;
					//Receive a text message
					case 4:
						message.clear();
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

		sf::Int8 type = 4;
		packet << type << message;

		sender.send(packet, myIP, 55001);
	}

	void NetworkHandler::sendMessageToEveryone(std::string message)
	{
		sf::Packet packet;

		sf::Int8 type = 3;
		packet << type << message;

		sender.send(packet, myIP, 55001);
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

	void NetworkHandler::connectToServer(std::string name)
	{
		sf::Int8 type = 1;
		sf::Packet packet;

		packet << type << name;

		sender.send(packet, myIP, 55001);

	}

	void NetworkHandler::notify(std::string e, void* object)
	{
		if(e == "connectToServer")
		{
			connectToServer("testClient");
		} else {
			sendMessageToEveryone(e);
		}
	}
}

