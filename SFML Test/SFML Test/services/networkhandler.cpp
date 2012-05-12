////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
// Class header
#include "networkhandler.h"

////////////////////////////////////////////////////////////
/// Network handler. Handles networking
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	/// Constructor
	////////////////////////////////////////////////////////////
    NetworkHandler::NetworkHandler(WorldData* worldData, World* model)
    {
		this->worldData = worldData;
		this->model = model;
		currentClientID = 1;

		hasConnected = false;

		receivePort = 55001;
		//Binds the receiving socket to a port
		if(receiver.bind(receivePort) == sf::Socket::Status::Error)
		{
			std::cout<<"Error binding to port "<<receivePort<<std::endl;
		}

		myIP = "192.168.1.41";
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

		b2Vec2 position;
		float32 x,y;
		b2Vec2 size;

		////////////////////////////////////////////////////////////
		/// Main loop of network handler.
		/// Constantly checks if there are any incoming data packets
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
				//Checks what type of packet has been sent and does
				//The appropriate thing with it
				switch(type)
				{
					//Client trying to connect
					case 1:
						//Creates a client from the data
						receivedData >> name >> x >> y;
	
						client.IP = senderIP;
						client.name = name;

						//adds that client to the clientmap
						clientMap[currentClientID] = client;
						currentClientID++;
						std::cout<<name<<" has connected with IP: "<<senderIP<<" from port: "<<senderPort<<std::endl;

						position.x = x;
						position.y = y;
						size.x = 1.0f;
						size.y = 2.0f;

						model->createCharacter(position, size);
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

						//If the clientMap is empty there are no clients to send to
						if(!clientMap.empty())
						{
							//Loops through the clientMap and sends the message to everyone
							for(sf::Int8 i = 1; i <= clientMap.size(); i++)
							{
								client = clientMap[i];
								sendMessage(message, client.IP);
								std::cout<<"Message sent to "<<client.IP<<std::endl;
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
	/// Destructor
	////////////////////////////////////////////////////////////
    NetworkHandler::~NetworkHandler()
    {
    }
	////////////////////////////////////////////////////////////
	/// Sends a message to selected IP-address
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendMessage(std::string message, sf::IpAddress IP)
	{
		sf::Packet packet;

		sf::Int8 type = 4;
		packet << type << message;

		sender.send(packet, IP, receivePort);
	}


	////////////////////////////////////////////////////////////
	/// Sends a message over the internet to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendMessageToServer(std::string message)
	{
		sf::Packet packet;

		sf::Int8 type = 4;
		packet << type << message;

		sender.send(packet, myIP, receivePort);
	}

	////////////////////////////////////////////////////////////
	/// Sends a message over the internet to the server
	/// which will then send the same message to all clients
	/// attached to it.
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendMessageToEveryone(std::string message)
	{
		sf::Packet packet;

		sf::Int8 type = 3;
		packet << type << message;

		sender.send(packet, myIP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Connects a client to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::connectToServer(std::string name)
	{
		sf::Int8 type = 1;
		sf::Packet packet;

		Character* character = worldData->getCurrentCharacter();
		float32 x = character->getBody()->GetPosition().x;
		float32 y = character->getBody()->GetPosition().y;

		packet << type << name << x << y;

		sender.send(packet, myIP, 55001);
		std::cout<<"Hej"<<std::endl;
	}

	////////////////////////////////////////////////////////////
	/// If the notification is connectToServer the client will try
	/// to connect to the server.
	///
	/// If it is a message not related to the network handler it will
	/// be sent to the the server as a text message and from the server
	/// sent to every client.
	////////////////////////////////////////////////////////////
	void NetworkHandler::notify(Event e, void* object)
	{
		if(e == CONNECT_SERVER)
		{
			if(!hasConnected)
			{
				hasConnected = true;
				connectToServer("testClient");
			}
		} else if(e == BULLET_ADDED) 
		{
			sendMessageToEveryone("Bullet added");
		} else if(e == BULLET_DELETED) 
		{
			sendMessageToEveryone("Bullet deleted");
		} else if(e == CHARACTER_ADDED)
		{
			sendMessageToEveryone("Character deleted");
		} else if(e == CHARACTER_DELETED)
		{
			sendMessageToEveryone("Bullet deleted");
		}
	}
}

