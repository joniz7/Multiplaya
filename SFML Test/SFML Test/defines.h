#ifndef DEFINES_H
#define DEFINES_H

#include <vector>
#include "sfml.h"

// Math
#define pi 3.14159265

// Enums
enum BulletType { GENERIC_BULLET };

// Structs
struct BulletData
{
	float force;
	short damage;
};

struct Animation{
	int fps;
	std::vector<sf::Vector2i> sequence;
};

#endif