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
	// Playback fps.
	float fps;
	// Should this animation loop?
	bool loop;
	// Sequence vector containing the frames in playback order.
	std::vector<sf::Vector2i> sequence;
};

#endif
