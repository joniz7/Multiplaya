#ifndef DEFINES_H
#define DEFINES_H

#include <vector>
#include "sfml.h"

// Math
#define pi 3.14159265

// Enums
enum BulletType { GENERIC_BULLET };

// Structs
struct BulletData {
	float force;
	short damage;
};

enum Event {
	BULLET_ADDED,
	BULLET_DELETED,
	CHARACTER_ADDED,
	CHARACTER_DELETED,
	CONNECT_SERVER
};

#endif
