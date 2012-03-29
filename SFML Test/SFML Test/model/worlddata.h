////////////////////////////////////////////////////////////
/// World data class. Holds all data used by world class for 
/// easy access from view and network handler.
////////////////////////////////////////////////////////////
#ifndef WORLDDATA_H_INCLUDED
#define WORLDDATA_H_INCLUDED

// Other headers
#include <string>
#include <vector>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include "../sfml.h"

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../game.h"

//Defines
#include "defines.h"

namespace mp
{
	//Forward declaration so WorldData can have a World pointer
	class World;

    class WorldData
    {
        public:
			WorldData(World* world);
            ~WorldData();

			//Adders
			bool addCharacter();
			bool addBullet( BulletType type, short owner, b2World* world, b2Vec2 position, b2Vec2 force );
			bool addBody( b2World* world, b2Vec2 position, b2Vec2 size );

			// Getters
			// Get list of all characters
			std::vector<Character>* getChrVec(){ return &chrVec; };
			// Get list of all bullets
			std::vector<Bullet>* getBltVec(){ return &bltVec; };
			// Get list of all bodies
			std::vector<b2Body*>* getBodyVec(){ return &bodyVec; };

			// Get a specific character
			Character* getCharacter(int i){ return &chrVec.at(i); };
			// Get a specific bullet
			Bullet* getBullet(int i){ return &bltVec.at(i); };
			// Get a specific body
			b2Body* getBody(int i){ return bodyVec.at(i); };

			//Other
			void ping();

		private:
			// Pointer to corresponding world object
			World* world;
			// Vector containing bullets
			std::vector<Bullet> bltVec;
			// Vector containing characters
			std::vector<Character> chrVec;
			// Vector containing generic Box2D bodies
			std::vector<b2Body*> bodyVec;
			
    };
}

#endif