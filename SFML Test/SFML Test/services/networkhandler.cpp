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
		myID = 0;

		hasConnected = false;

		receivePort = 55001;
		//Binds the receiving socket to a port
		if(receiver.bind(receivePort) == sf::Socket::Error)
		{
			std::cout<<"Error binding to port " << receivePort << std::endl;
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

		sf::Int8 clientID, numOfChars;

		std::string message;

		sf::Packet packet;

		b2Vec2 position, size, velocity;
		float32 x,y,xvel,yvel,angle;

		std::vector<Character*>* characters;

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

						std::cout<<name<<" has connected with IP: "<<senderIP<<" from port: "<<senderPort<<std::endl;

						position.x = x;
						position.y = y;
						size.x = 1.0f;
						size.y = 2.0f;

						model->createCharacter(position, size, currentClientID);

						sendClientID(currentClientID);
						currentClientID++;
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
					//Receives character data from a client.
					case 4:
						receivedData >> clientID >> x >> y >> xvel >> yvel >> angle;

						position.Set(x,y);
						velocity.Set(xvel, yvel);

						setCharacterData(clientID, position, velocity, angle);
						break;
					//Recieve your ID from the server
					case 11:
						receivedData >> myID;
						hasConnected = true;
						break;
					//Receive a text message
					case 12:
						message.clear();
						receivedData >> message;
						std::cout<<"Recieved a message: "<<message<<std::endl;
						break;
					//Receive character data from the server
					case 13:
						receivedData >> numOfChars;

						for(int i = 0; i<numOfChars; i++)
						{
							receivedData >> clientID >> x >> y >> xvel >> yvel >> angle;
							position.Set(x,y);
							velocity.Set(xvel, yvel);

							setCharacterData(clientID, position, velocity, angle);
						}
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

		sf::Int8 type = 12;
		packet << type << message;

		sender.send(packet, IP, receivePort);
	}


	////////////////////////////////////////////////////////////
	/// Sends a message over the internet to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendMessageToServer(std::string message)
	{
		sf::Packet packet;

		sf::Int8 type = 12;
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

		// should probably be something like getPlayer->getCurrentCharacter()
		Character* character = worldData->getCurrentCharacter();
		float32 x = character->getBody()->GetPosition().x;
		float32 y = character->getBody()->GetPosition().y;

		packet << type << name << x << y;

		sender.send(packet, myIP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Sends the data of a character to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendCharacterDataToServer()
	{
		sf::Int8 type = 4;
		sf::Packet packet;

		float32 x = worldData->getCurrentCharacter()->getBody()->GetPosition().x;
		float32 y = worldData->getCurrentCharacter()->getBody()->GetPosition().y;
		float32 xvel = worldData->getCurrentCharacter()->getBody()->GetLinearVelocity().x;
		float32 yvel = worldData->getCurrentCharacter()->getBody()->GetLinearVelocity().y;
		float32 angle = worldData->getCurrentCharacter()->getBody()->GetAngle();

		packet << type << myID << x << y << xvel << yvel << angle;
		sender.send(packet, myIP, 55001);

	}

	

	////////////////////////////////////////////////////////////
	/// Sends the client ID to the specified client
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendClientID(sf::Int8 ID)
	{
		sf::Packet packet;
		sf::Int8 type = 11;

		packet << type << ID;

		sender.send(packet, clientMap[ID].IP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Updates the position, linear velocity and angle of the specified
	/// character
	////////////////////////////////////////////////////////////
	void NetworkHandler::setCharacterData(sf::Int8 clientID, b2Vec2 position, b2Vec2 velocity, float32 angle)
	{
		Character* character = worldData->getCharacter(clientID);

		character->setPosition(position, angle);
		character->setLinVelocity(velocity);
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

