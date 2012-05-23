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

		sendOutput = false;


		//Binds the receiving socket to any port
		if(receiver.bind(sf::UdpSocket::AnyPort) == sf::Socket::Error)
		{
			std::cout<<"Error binding tsdfasdfsao port " << receivePort << std::endl;
		}

		receivePort = receiver.getLocalPort();

		serverIP = serverIP.getLocalAddress();
		std::cout<<"Your IP is: "<<serverIP<<std::endl;

		clientMap[myID].IP = serverIP;
		clientMap[myID].name = "host";
		clientMap[myID].port = 55001;
    }

	void NetworkHandler::exec() 
	{

		//Data about sender
		sf::Packet receivedData;
		sf::IpAddress senderIP;
		unsigned short senderPort, senderLocalPort;

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
		int outputType, test;

		bool grounded, walking, facingLeft, touchingLeftWall, touchingRightWall, wallSliding, flipping;

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
					//std::cout << "before" << (*it).second.disconnectCounter << std::endl;
					//std::cout << (*it).second.IP << "    " << senderIP << std::endl;
					if((*it).second.IP == senderIP)
					{
						(*it).second.disconnectCounter = 0;
					}
					else
					{
						(*it).second.disconnectCounter++;
						if((*it).second.disconnectCounter == 400)
						{
							//disconnectClient((*it).first);
						}
					}
					//std::cout << "after" << (*it).second.disconnectCounter << std::endl;
				}
			}
			

			//Tries to read what type of message the packet was
			if(!(receivedData >> type))
				std::cout<<"Error reading data from packet"<<std::endl;
			else 
			{
				outputType = type;
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
							if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

							receivedData >> name >> x >> y >> senderLocalPort;

							client.IP = senderIP;
							client.name = name;
							client.disconnectCounter = 0;
							client.port = senderLocalPort;

							//adds that client to the clientmap
							clientMap[currentClientID] = client;

							std::cout<<name<<" has connected with IP: "<<senderIP<<" from port: "<<client.port<<std::endl;

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
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

						//std::cout<<"type 2"<<std::endl;
						receivedData >> clientID;

						client = clientMap[clientID];

						std::cout<<client.name<<" has disconnected"<<std::endl;

						clientMap.erase(clientID);
						break;

					//Receive a text message and send it to all clients
					case 3:
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

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
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

						//std::cout<<"type 4"<<std::endl;
						receivedData >> clientID >> x >> y >> xvel >> yvel >> angle >> grounded >> walking >> facingLeft >>  touchingLeftWall >> touchingRightWall >> wallSliding >> flipping;
						position.Set(x,y);
						velocity.Set(xvel, yvel);
						test = clientID;

						setCharacterData(clientID, position, velocity, angle, grounded, walking, facingLeft, touchingLeftWall, touchingRightWall, wallSliding, flipping);
						break;
					//Receive bullet data from a client
					case 5:
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

						//std::cout<<"type 5"<<std::endl;
						receivedData >> numOfBullets;

						//All the bullets in the packet is added to the world
						for(int i = 0; i<numOfBullets; i++)
						{
							receivedData >> clientID >> x >> y >> xvel >> yvel;

							position.Set(x,y);
							velocity.Set(xvel, yvel);

							model->createBullet(position, velocity, clientID);
						}
						break;
					//Recieve your ID from the server
					case 11:
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

						//std::cout<<"type 11"<<std::endl;
						receivedData >> myID;
						worldDataMutex.lock();
						worldData->getCharacter(0)->setClientID(myID);
						worldDataMutex.unlock();
						hasConnected = true;
						worldData->setAsClient();
						break;
					//Receive a text message
					case 12:
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

						//std::cout<<"type 12"<<std::endl;
						message.clear();
						receivedData >> message;
						std::cout<<"Recieved a message: "<<message<<std::endl;
						break;
					//Receive character data from the server
					case 13:
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

						//std::cout<<"type 13"<<std::endl;
						receivedData >> numOfChars;

						for(int i = 0; i<numOfChars; i++)
						{
							receivedData >> clientID >> x >> y >> xvel >> yvel >> angle >> grounded >> walking >> facingLeft >>  touchingLeftWall >> touchingRightWall >> wallSliding >> flipping;
							position.Set(x,y);
							velocity.Set(xvel, yvel);

							setCharacterData(clientID, position, velocity, angle, grounded, walking, facingLeft, touchingLeftWall, touchingRightWall, wallSliding, flipping);
						}
						break;
					//Receive bullet data from the server
					case 14:
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

						//std::cout<<"type 14"<<std::endl;
						receivedData >> numOfBullets;
						if(numOfBullets > 0)
						{
							//worldDataMutex.lock();
							//The current bullet list is cleared
							if(worldData->getBullets()->size()>0)
							{
								worldData->removeAllBullets(myID);
							}
						
							//And replaced by the new bullets
							for(int i = 0; i<numOfBullets; i++)
							{
								receivedData >> clientID >> x >> y >> xvel >> yvel;
								if((x != 0 && y != 0) && (xvel != 0 && yvel != 0))
								{

								position.Set(x,y);
								velocity.Set(xvel, yvel);

								model->createBullet(position, velocity, clientID);
								}
							}
						}
						//worldDataMutex.unlock();
						break;
					//Receive characters to create from the server
					case 15:
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

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
						if(sendOutput)
								std::cout<<"type "<<outputType<<std::endl;

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

		sender.send(packet, IP, 55001);
	}


	////////////////////////////////////////////////////////////
	/// Sends a message over the internet to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendMessageToServer(std::string message)
	{
		sf::Packet packet;

		sf::Int8 type = 12;
		packet << type << message;

		sender.send(packet, serverIP, 55001);
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
		sf::Int8 type = 1, port = receivePort;
		sf::Packet packet;

		worldDataMutex.lock();
		ICharacter* character = worldData->getCurrentCharacter();
		float32 x = character->getBody()->GetPosition().x;
		float32 y = character->getBody()->GetPosition().y;
		worldDataMutex.unlock();

		packet << type << name << x << y << port;

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
		sf::Uint16 port = receivePort;
		sf::Packet packet;

		worldDataMutex.lock();
		ICharacter* character = worldData->getCurrentCharacter();
		float32 x = character->getBody()->GetPosition().x;
		float32 y = character->getBody()->GetPosition().y;
		worldDataMutex.unlock();

		packet << type << name << x << y << port;

		std::cout<<"Connecting to server IP "<<serverIP<<" and listening to port: "<<receivePort<<std::endl;

		sender.send(packet, serverIP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Disconnect the given client from the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::disconnectClient(sf::Int8 clientID)
	{
		Client client = clientMap[clientID];

		std::cout<<client.name<<" has disconnected"<<std::endl;

		std::map<sf::Int8, Client>::iterator it;
		it = clientMap.find(clientID);
		
		/*
		if(it != clientMap.end())
			clientMap.erase(it);
		*/

		removeCharacter(clientID);
	}

	////////////////////////////////////////////////////////////
	/// Sends the data of a character to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendCharacterDataToServer()
	{
		sf::Int8 type = 4;
		sf::Packet packet;

		worldDataMutex.lock();
		float32 x = worldData->getCurrentCharacter()->getPosition().x;
		float32 y = worldData->getCurrentCharacter()->getPosition().y;
		float32 xvel = worldData->getCurrentCharacter()->getLinVelocity().x;
		float32 yvel = worldData->getCurrentCharacter()->getLinVelocity().y;
		float32 angle = worldData->getCurrentCharacter()->getAngle();
		bool grounded = worldData->getCurrentCharacter()->isGrounded();
		bool walking = worldData->getCurrentCharacter()->isWalking();
		bool facingLeft = worldData->getCurrentCharacter()->isFacingLeft();
		bool touchingLeftWall = worldData->getCurrentCharacter()->isTouchingWallLeft();
		bool touchingRightWall = worldData->getCurrentCharacter()->isTouchingWallRight();
		bool wallSliding = worldData->getCurrentCharacter()->isWallSliding();
		bool flipping = worldData->getCurrentCharacter()->isFlipping();
		worldDataMutex.unlock();

		packet << type << myID << x << y << xvel << yvel << angle << grounded << walking << facingLeft <<  touchingLeftWall << touchingRightWall << wallSliding << flipping;
		sender.send(packet, serverIP, 55001);
	}

	////////////////////////////////////////////////////////////
	/// Sends the data of all the character to the specified client
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendCharacterDataToClient(sf::Int8 clientID)
	{
		sf::Int8 type = 13, tempClientID, numOfChars = worldData->getCharacters()->size();
		sf::Packet packet;
		ICharacter* tempCharacter;
		float32 x, y, xvel, yvel, angle;
		bool grounded, walking, facingLeft, touchingLeftWall, touchingRightWall, wallSliding, flipping;
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
			grounded = tempCharacter->isGrounded();
			walking = tempCharacter->isWalking();
			facingLeft = tempCharacter->isFacingLeft();
			touchingLeftWall = tempCharacter->isTouchingWallLeft();
			touchingRightWall = tempCharacter->isTouchingWallRight();
			wallSliding = tempCharacter->isWallSliding();
			flipping = tempCharacter->isFlipping();

			if(tempClientID != clientID)
				packet << tempClientID << x << y << xvel << yvel << angle << grounded << walking << facingLeft <<  touchingLeftWall << touchingRightWall << wallSliding << flipping;
		}

		sender.send(packet, clientMap[clientID].IP, clientMap[clientID].port);
	}

	////////////////////////////////////////////////////////////
	/// Sends all characters to a client and tells it to create them
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendCharactersToClient(sf::Int8 clientID)
	{
		sf::Int8 type = 15, tempClientID, numOfChars = worldData->getCharacters()->size()-1;
		sf::Packet packet;
		ICharacter* tempCharacter;
		float32 x, y;
		packet << type << numOfChars;

		for(int i = 0; i < numOfChars; i++)
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
		std::cout<<"Sending characters to "<<clientMap[clientID].name<<", to port "<<clientMap[clientID].port<<std::endl;
		sender.send(packet, clientMap[clientID].IP, clientMap[clientID].port);
	}

	////////////////////////////////////////////////////////////
	/// Removes the selected character from the world and view
	////////////////////////////////////////////////////////////
	void NetworkHandler::removeCharacter(sf::Int8 clientID)
	{
		worldData->removeCharacter(clientID);

		sf::Int8 type = 16;
		sf::Packet packet;
		std::map<sf::Int8, Client>::iterator it;
		
		for(it = clientMap.begin(); it != clientMap.end(); it++)
		{
			if(it != clientMap.end())
				sender.send(packet, (*it).second.IP, clientMap[clientID].port);
		}
	}

	////////////////////////////////////////////////////////////
	/// Sends the data of all the characters to the all clients
	////////////////////////////////////////////////////////////
	void NetworkHandler::updateAllClients()
	{
		std::map<sf::Int8, Client>::iterator it;

		for(it = clientMap.begin(); it != clientMap.end(); it++)
		{
			//We don't want to send data back to the server
			if(it != clientMap.end() && (*it).first != 0)
			{
				worldDataMutex.lock();
				sendCharacterDataToClient((*it).first);
				sendBulletDataToClient((*it).first);
				worldDataMutex.unlock();
			}
		}
	}

	////////////////////////////////////////////////////////////
	/// Sends the client ID to the specified client
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendClientID(sf::Int8 clientID)
	{
		sf::Packet packet;
		sf::Int8 type = 11;

		packet << type << clientID;

		sender.send(packet, clientMap[clientID].IP, clientMap[clientID].port);
	}

	////////////////////////////////////////////////////////////
	/// Sends all the bullets in the world to a specified client
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendBulletDataToClient(sf::Int8 clientID)
	{
		sf::Int8 type = 14, tempClientID, numOfBullets = 0;
		sf::Packet packet;
		Bullet* tempBullet;
		float32 x, y, xvel, yvel;

		for(int i = 0; i<worldData->getBullets()->size(); i++)
		{
			tempBullet = worldData->getBullet(i);
			if(tempBullet->getOwner() != clientID)
			{
				numOfBullets++;
			}
		}

		packet << type << numOfBullets;

		if(numOfBullets > 0)
		{
			for(int i = 0; i<numOfBullets; i++)
			{
				tempBullet = worldData->getBullet(i);
				if(tempBullet->getOwner() != clientID)
				{
					tempClientID = tempBullet->getOwner();
					x = tempBullet->getPosition().x;
					y = tempBullet->getPosition().y;
					xvel = tempBullet->getLinVelocity().x;
					yvel = tempBullet->getLinVelocity().y;

					packet << tempClientID << x << y << xvel << yvel;
				}
			}
		}
		
		sender.send(packet, clientMap[clientID].IP, clientMap[clientID].port);
	}

	////////////////////////////////////////////////////////////
	/// Sends the bullets created by the client to the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::sendBulletDataToServer()
	{
		if(bulletsToSend.size()>0)
		{
			sf::Int8 type = 5, numOfBullets = bulletsToSend.size();
			sf::Packet packet;
			BufferBullet tempBullet;
			float32 x, y, xvel, yvel;
			packet << type << numOfBullets;

			for(int i = 0; i<numOfBullets; i++)
			{
				tempBullet = bulletsToSend.at(i);
				x = tempBullet.x;
				y = tempBullet.y;
				xvel = tempBullet.xvel;
				yvel = tempBullet.yvel;

				packet << myID << x << y << xvel << yvel;
			}

			bulletsToSend.clear();

			sender.send(packet, serverIP, 55001);
		}
	}

	////////////////////////////////////////////////////////////
	/// Updates the position, linear velocity and angle of the specified
	/// character
	////////////////////////////////////////////////////////////
	void NetworkHandler::setCharacterData(sf::Int8 clientID, b2Vec2 position, b2Vec2 velocity, float32 angle, bool grounded, bool walking, bool facingLeft, bool touchingWallLeft, bool touchingWallRight, bool wallSliding, bool flipping)
	{
		worldDataMutex.lock();
		if(worldData->exists(clientID))
		{
			ICharacter* character = worldData->getCharacter(clientID);
			character->setPosition(position, angle);
			character->setLinVelocity(velocity);
			character->setGrounded(grounded);
			character->setWalking(walking);
			character->setIsFacingLeft(facingLeft);
			character->setTouchingWallLeft(touchingWallLeft);
			character->setTouchingWallRight(touchingWallRight);
			character->setWallSliding(wallSliding);
			character->setFlipping(flipping);
		}
		worldDataMutex.unlock();
	}

	////////////////////////////////////////////////////////////
	/// Sets the IPAddress of the server
	////////////////////////////////////////////////////////////
	void NetworkHandler::setIPAddress(const sf::String IPAddress)
	{
		serverIP = IPAddress.toAnsiString();
	}

	////////////////////////////////////////////////////////////
	/// Makes the networkhandler a client.
	////////////////////////////////////////////////////////////
	void NetworkHandler::setAsClient()
	{
		isClient = true;
	}


	////////////////////////////////////////////////////////////
	/// Makes the networkhandler a server.
	/// Binds the receiver socket to a specified port so
	/// a client knows where to send packets.
	////////////////////////////////////////////////////////////
	void NetworkHandler::setAsServer()
	{
		isServer = true;
		receiver.unbind();
		receiver.bind(55001);
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
		} 
		else if(e == SEND_BULLET) 
		{
			//sendMessageToEveryone("Bullet added to buffer");
			Bullet* tempBullet = (Bullet*) object;
			float32 x = tempBullet->getPosition().x;
			float32 y = tempBullet->getPosition().y;
			float32 xvel = tempBullet->getInitForce().x;
			float32 yvel = tempBullet->getInitForce().y;

			sf::Packet packet;
			sf::Int8 type = 5, quantity = 1;
			packet << type << quantity << myID << x << y << xvel << yvel;
			sender.send(packet, serverIP, 55001);
		} 
		else if(e == BULLET_DELETED) 
		{
			//sendMessageToEveryone("Bullet deleted");
		} 
		else if(e == CHARACTER_ADDED)
		{
			sendMessageToEveryone("Character added");
		} 
		else if(e == CHARACTER_DELETED)
		{
			sendMessageToEveryone("Character deleted");
		}
	}
}

