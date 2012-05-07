#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "sfml.h"

struct Client{
	sf::IpAddress IP;
	std::string name;
};

#endif