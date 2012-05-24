#ifndef CLIENT_H
#define CLIENT_H

#include <string>

struct Client{
	sf::IpAddress IP;
	std::string name;
	unsigned short port;
	int disconnectCounter;
	short kills;
	short deaths;
};

#endif