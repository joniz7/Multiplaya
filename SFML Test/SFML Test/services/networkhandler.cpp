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

		isServer = false;
		isClient = false;

		hasConnected = false;

		receivePort = 55001;
		//Binds the receiving socket to a port
		if(receiver.bind(receivePort) == sf::Socket::Error)
		{
			std::cout<<"Error binding to port " << receivePort << std::endl;
		}

		serverIP = serverIP.getLocalAddress();
		std::cout<<"Your IP is: "<<serverIP<<std::endl;

		clientMap[myID].IP = serverIP;
		clientMap[myID].name = "host";
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

		sf::Int8 clientID, numOfChars, numOfBullets;

		std::string message;

		sf::Packet packet;

		b2Vec2 position, size, velocity;
		float32 x,y,xvel,yvel,angle;

		std::vector<Character*>* characters;

		std::map<sf::Int8, Client>::iterator it;
		int test;

		////////////////////////////////////////////////////////////
		/// Main loop of network handler.
		/// Constantly checks if there are any incoming data packets
		////////////////////////////////////////////////////////////
		while(running) 
		{
			//Receives a packet
			//std::cout<<"Receiving data..."<<std::endl;
			receivedData.clear();
			receiver.receive(receivedData, senderIP, senderPort);
			if(isServer)
			{
				for(it = clientMap.begin(); it != clientMap.end(); it++)
				{
					if((*it).second.IP == senderIP)
					{
						(*it).second.disconnectCounter = 0;
					}
					else
					{
						(*it).second.disconnectCounter++;
						if((*it).second.disconnectCounter == 20)
						{

						}
					}
				}
			}

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
						//std::cout<<"type 1"<<std::endl;
						//Creates a client from the data
						if(isServer) 
						{
							receivedData >> name >> x >> y;
	
							client.IP = senderIP;
							client.name = name;
							client.disconnectCounter = 0;

							//adds that client to the clientmap
							clientMap[currentClientID] = client;

							std::cout<<name<<" has connected with IP: "<<senderIP<<" from port: "<<senderPort<<std::endl;

							position.x = x;
							position.y = y;
							size.x = 1.0f;
							size.y = 2.0f;

							model->createCharacter(position, size, currentClientID);

							sendClientID(currentClientID);
							sendCharactersToClient(currentClientID);
							currentClientID++;
						}
						break;

					//Client trying to disconnect
					case 2:
						//std::cout<<"type 2"<<std::endl;
						receivedData >> clientID;

						client = clientMap[clientID];

						std::cout<<client.name<<" has disconnected"<<std::endl;

						clientMap.erase(clientID);
						break;

					//Receive a text message and send it to all clients
					case 3:
						//std::cout<<"type 3"<<std::endl;
						message.clear();
						receivedData >> message;
						//std::cout<<"Recieved a message: "<<message<<std::endl;

						//If the clientMap is empty there are no clients to send to
						if(!clientMap.empty())
						{
							for(it = clientMap.begin(); it != clientMap.end(); it++)
							{
								sendMessage(message, (*it).second.IP);
								std::cout<<"Message sent to "<<(*it).second.IP<<std::endl;
							}
						}

						break;
					//Receive character data from a client.
					case 4:
						//std::cout<<"type 4"<<std::endl;
						receivedData >> clientID >> x >> y >> xvel >> yvel >> angle;
						test = worldData->getCharacter(0)->getClientID();
						position.Set(x,y);
						velocity.Set(xvel, yvel);

						//setCharacterData(clientID, position, velocity, angle);
						break;
					//Receive bullet data from a client
					case 5:
						//std::cout<<"type 5"<<std::endl;
						receivedData >> numOfBullets;

						//All the bullets in the packet is added to the world
						for(int i = 0; i<numOfBullets; i++)
						{
							receivedData >> clientID >> x >> y >> xvel >> yvel;

							position.Set(x,y);
							velocity.Set(xvel, yvel);

							model->createBullet(position, velocity, clientID, GENERIC_BULLET);
						}
						break;
					//Recieve your ID from the server
					case 11:
						//std::cout<<"type 11"<<std::endl;
						receivedData >> myID;
						worldDataMutex.lock();
						worldData->getCharacter(0)->setClientID(myID);
						worldDataMutex.unlock();
						hasConnected = true;
						break;
					//Receive a text message
					case 12:
						//std::cout<<"type 12"<<std::endl;
						message.clear();
						receivedData >> message;
						std::cout<<"Recieved a message: "<<message<<std::endl;
						break;
					//Receive character data from the server
					case 13:
						//std::cout<<"type 13"<<std::endl;
						receivedData >> numOfChars;

						for(int i = 0; i<numOfChars; i++)
						{
							receivedData >> clientID >> x >> y >> xvel >> yvel >> angle;
							position.Set(x,y);
							velocity.Set(xvel, yvel);

							setCharacterData(clientID, position, velocity, angle);
						}
						break;
					//Receive bullet data from the server
					case 14:
						//std::cout<<"type 14"<<std::endl;
						receivedData >> numOfBullets;

						//The current bullet list is cleared
						worldData->getBullets()->clear();

						//And replaced by the new bullets
						for(int i = 0; i<numOfBullets; i++)
						{
							receivedData >> clientID >> x >> y >> xvel >> yvel;

							position.Set(x,y);
							velocity.Set(xvel, yvel);

							model->createBullet(position, velocity, clientID, GENERIC_BULLET);
						}
						break;
					//Receive character data from the server
					case 15:
						std::cout<<"type 15"<<std::endl;
						receivedData >> numOfChars;

						size.Set(1.0f, 2.0f);

						for(int i = 0; i<numOfChars; i++)
						{
							receivedData >> clientID >> x >> y;
							position.Set(x,y);

							model->createCharacter(position, size, clientID);

						}
						break;
					//Remove the specified character
					case 16:
						std::cout<<"type 16"<<std::endl;
						receivedData >> clientID;

						worldData->removeCharacter(clientID);
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

		sender.send(packet, serverIP, receivePort);
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

		sender.send(packet, serverIP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Connects a client to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::connectToServer(std::string name)
	{
		sf::Int8 type = 1;
		sf::Packet packet;

		worldDataMutex.lock();
		Character* character = worldData->getCurrentCharacter();
		float32 x = character->getBody()->GetPosition().x;
		float32 y = character->getBody()->GetPosition().y;
		worldDataMutex.unlock();

		packet << type << name << x << y;

		std::cout<<"Connecting to server IP: "<<serverIP<<std::endl;

		sender.send(packet, serverIP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Connects a client to the server with the given IPAddress
	////////////////////////////////////////////////////////////
	void NetworkHandler::connectToServer(std::string name, std::string IPAddress)
	{
		serverIP = IPAddress;
		sf::Int8 type = 1;
		sf::Packet packet;

		worldDataMutex.lock();
		Character* character = worldData->getCurrentCharacter();
		float32 x = character->getBody()->GetPosition().x;
		float32 y = character->getBody()->GetPosition().y;
		worldDataMutex.unlock();

		packet << type << name << x << y;

		std::cout<<"Connecting to server IP: "<<serverIP<<std::endl;

		sender.send(packet, serverIP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Disconnect the given client from the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::disconnectClient(sf::Int8 clientID)
	{
		Client client = clientMap[clientID];

		std::cout<<client.name<<" has disconnected"<<std::endl;

		clientMap.erase(clientID);
	}

	////////////////////////////////////////////////////////////
	/// Sends the data of a character to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendCharacterDataToServer()
	{
		sf::Int8 type = 4;
		sf::Packet packet;

		worldDataMutex.lock();
		float32 x = worldData->getCurrentCharacter()->getBody()->GetPosition().x;
		float32 y = worldData->getCurrentCharacter()->getBody()->GetPosition().y;
		float32 xvel = worldData->getCurrentCharacter()->getBody()->GetLinearVelocity().x;
		float32 yvel = worldData->getCurrentCharacter()->getBody()->GetLinearVelocity().y;
		float32 angle = worldData->getCurrentCharacter()->getBody()->GetAngle();
		worldDataMutex.unlock();

		packet << type << myID << x << y << xvel << yvel << angle;
		sender.send(packet, serverIP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Sends the data of all the character to the specified client
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendCharacterDataToClient(sf::Int8 clientID)
	{
		sf::Int8 type = 13, tempClientID, numOfChars = worldData->getCharacters()->size();
		sf::Packet packet;
		Character* tempCharacter;
		float32 x, y, xvel, yvel, angle;
		packet << type << numOfChars;

		for(int i = 0; i<numOfChars; i++)
		{
			tempCharacter = worldData->getCharacter(i);
			tempClientID = tempCharacter->getClientID();
			x = tempCharacter->getPosition().x;
			y = tempCharacter->getPosition().y;
			xvel = tempCharacter->getLinVelocity().x;
			yvel = tempCharacter->getLinVelocity().y;
			angle = tempCharacter->getAngle();

			packet << tempClientID << x << y << xvel << yvel << angle;
		}

		sender.send(packet, clientMap[clientID].IP, receivePort);
	}

	////////////////////////////////////////////////////////////
	/// Sends all characters to a client and tells it to create them
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendCharactersToClient(sf::Int8 clientID)
	{
		sf::Int8 type = 15, tempClientID, numOfChars = worldData->getCharacters()->size();
		sf::Packet packet;
		Character* tempCharacter;
		float32 x, y;
		packet << type << numOfChars;

		for(int i = 0; i<numOfChars; i++)
		{
			tempCharacter = worldData->getCharacter(i);
			tempClientID = tempCharacter->getClientID();
			x = tempCharacter->getPosition().x;
			y = tempCharacter->getPosition().y;

			if(tempClientID != clientID)
			{
				packet << tempClientID << x << y;
			}
		}

		sender.send(packet, clientMap[clientID].IP, receivePort);
	}

	void NetworkHandler::removeCharacter(sf::Int8 clientID)
	{
		worldData->removeCharacter(clientID);

		sf::Int8 type = 16;
		sf::Packet packet;
		std::map<sf::Int8, Client>::iterator it;
		
		for(it = clientMap.begin(); it != clientMap.end(); it++)
		{
			sender.send(packet, (*it).second.IP, 55001);
		}
	}

	////////////////////////////////////////////////////////////
	/// Sends the data of all the character to the all clients
	////////////////////////////////////////////////////////////
	void NetworkHandler::updateAllClients()
	{
		std::map<sf::Int8, Client>::iterator it;

		for(it = clientMap.begin(); it != clientMap.end(); it++)
		{
			sendCharacterDataToClient((*it).first);
		}
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
		worldDataMutex.lock();
		Character* character = worldData->getCharacter(clientID);
		character->setPosition(position, angle);
		character->setLinVelocity(velocity);
		worldDataMutex.unlock();
	}

	void NetworkHandler::setIPAddress(const sf::String IPAddress)
	{
		serverIP = IPAddress.toAnsiString();
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
			sendMessageToEveryone("Bullet added to buffer");
			//bulletsToSend.push_back((Bullet*)object);
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

