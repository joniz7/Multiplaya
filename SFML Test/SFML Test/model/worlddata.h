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
// SFML specific headers
#include <sfml.h>

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../game.h"

//Defines
#include "../defines.h"

#include "Player.h"
#include "Wall.h"

#include "../util/Observable.h"

namespace mp
{
	//Forward declaration so WorldData can have a World pointer
	//class World;
	class Player;
	class Bullet;
	class Character;

    class WorldData : public Observable
    {
        public:
			WorldData();
            ~WorldData();

			//Adders
			bool addCharacter(b2World* world, b2Vec2 position, b2Vec2 size);
			bool addBullet( Bullet* bullet );
			bool addBullet( BulletType type, short owner, b2World* world, b2Vec2 position, b2Vec2 force );
			bool addBody( b2World* world, b2Vec2 position, b2Vec2 size );
			bool addBody ( b2Body* body );
			void addWall( b2World* world, float xPos, float yPos, float width, float height);
			void createPlayer();
			// Getters
			// Get list of all characters
			std::vector<Character>* getCharacters(){ return &characters; };
			// Get list of all bullets
			std::vector<Bullet*>* getBullets(){ return &bullets; };
			std::vector<Bullet*>* getBulletsToRemove() { return &bulletsToRemove; }
			// Get list of all bodies
			std::vector<b2Body*>* getBodies(){ return &bodies; };
			b2Vec2 getMousePosition() {return *mousePosition;}
			// Get a specific character
			Character* getCharacter(int i){ return &characters.at(i); };
			// Get a specific bullet
			Bullet* getBullet(int i){ return bullets.at(i); };
			// Get a specific body
			b2Body* getBody(int i){ return bodies.at(i); };

			//b2World* getb2World();

			Player* getPlayer() { return player; }
			// Get logic fps
			int getLogicFps(){return logicFps;};

			void scheduleBulletForDeletion(Bullet* bullet);
			void removeBullet(Bullet* bullet);

			// Setters
			// Set logic fps
			void setLogicFps(int fps){logicFps = fps;};

			void setMousePosition(sf::Vector2f* pos);	

		private:
			// Pointer to corresponding world object
			//World* world;
			// Vector containing bullets
			std::vector<Bullet*> bullets;
			// A queue, containing all bullets scheduled for deletion.
			std::vector<Bullet*> bulletsToRemove;
			// Vector containing characters
			std::vector<Character> characters;
			std::vector<Wall*> walls;
			// Vector containing generic Box2D bodies
			std::vector<b2Body*> bodies;
			// The mouse position (in world coordinates)
			b2Vec2* mousePosition;
			// Variable for keeping track of logic thread fps
			int logicFps;
			Player* player;
    };
}

#endif
