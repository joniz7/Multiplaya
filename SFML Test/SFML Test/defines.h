#ifndef DEFINES_H
#define DEFINES_H

// Math
#define pi 3.14159265
const float PIXEL_SCALE = 1 / 10.0f;

// Enums
enum BulletType { GENERIC_BULLET };

// Structs
struct BulletData {
	float force;
	short damage;
};

#endif
