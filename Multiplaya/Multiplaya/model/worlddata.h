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
#include <algorithm>

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "character.h"
#include "bullet.h"

//Defines
#include "../defines.h"

#include "Wall.h"
#include "worldchain.h"

#include "../util/Observable.h"

namespace mp
{
	//Forward declaration so WorldData can have a World pointer
	//class World;
	class Bullet;
	class Character;

    class WorldData : public Observable, public Observer
    {
        public:
			WorldData();
            ~WorldData();

			//Adders
			bool addCharacter(Character* c);
			bool addCharacter(b2World* world, b2Vec2 pos, b2Vec2 size, sf::Int8 clientID);
			void removeCharacter(sf::Int8 ID);

			bool addBullet( Bullet* bullet );
			bool addBullet( BulletType type, short owner, b2World* world, b2Vec2 position, b2Vec2 force );
			bool addBody( b2World* world, b2Vec2 position, b2Vec2 size );
			bool addBody ( b2Body* body );
			void addWall( b2World* world, float xPos, float yPos, float width, float height);
			void addChain( b2World* world, b2Vec2 vertices[], int length, float friction );
			void clearPhysics();

			//Does this character exist?
			bool exists(sf::Int8 clientID);

			// Getters
			// Get list of all characters
			std::vector<Character*>* getCharacters(){ return &characters; };
			// Get list of all bullets
			std::vector<Bullet*>* getBullets(){ return &bullets; };
			std::vector<Bullet*>* getBulletsToRemove() { return &bulletsToRemove; }
			// Get list of all bodies
			std::vector<b2Body*>* getBodies(){ return &bodies; };

			// Get a specific character
			Character* getCharacter(int i){ return characters.at(i); };
			// Get the character with the specific client ID
			Character* getCharacter(sf::Int8 clientID);
			// Get a specific bullet
			Bullet* getBullet(int i){ return bullets.at(i); };
			// Get a specific body
			b2Body* getBody(int i){ return bodies.at(i); };

			//b2World* getb2World();

			// Get logic fps
			int getLogicFps(){ return logicFps; }

			void scheduleBulletForDeletion(Bullet* bullet);
			void removeBullet(Bullet* bullet);

			// Setters
			// Set logic fps
			void setLogicFps(int fps){logicFps = fps;};

			void setCurrentCharacterId(int id) {currentCharacterId = id;}
			int getCurrentCharacterId() {return currentCharacterId;}

			virtual void notify(Event e, void* object);
			Character* getCurrentCharacter() {return characters.at(currentCharacterId);}
		private:
			int currentCharacterId;
			// Pointer to corresponding world object
			//World* world;
			// Vector containing bullets
			std::vector<Bullet*> bullets;
			// A queue, containing all bullets scheduled for deletion.
			std::vector<Bullet*> bulletsToRemove;
			// Vector containing characters
			std::vector<Character*> characters;
			std::vector<Wall*> walls;
			std::vector<WorldChain*> chains;
			// Vector containing generic Box2D bodies
			std::vector<b2Body*> bodies;

			// Variable for keeping track of logic thread fps
			int logicFps;
    };
}

#endif
