#ifndef CLIENT_H
#define CLIENT_H

#include <string>

struct Client{
	sf::IpAddress IP;
	std::string name;
	unsigned short port;
	int disconnectCounter;
};

struct BufferBullet
{
	float32 x;
	float32 y;
	float32 xvel;
	float32 yvel;
};

#endif