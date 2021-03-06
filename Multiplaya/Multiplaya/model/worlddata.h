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
#include "gameobjects/DefaultCharacter.h"
#include "gameobjects/StandardBullet.h"

#include "worldchain.h"

namespace mp
{
	//Forward declarations.
	//class World;
	class IBullet;
	class ICharacter;

	/**
	 * Holds all model data related to the game.
	 * Contains all characters, bullets and the map.
	 */
    class WorldData : public Observable, public Observer
    {
        public:
			WorldData();
            ~WorldData();
			void reset();

			//Adders
			void addCharacter(ICharacter* c);
			void addCharacter(b2World* world, b2Vec2 pos, b2Vec2 size, sf::Int8 clientID);
			void removeCharacter(sf::Int8 ID);

			void addBullet( IBullet* bullet );
			void addBullet( short owner, b2World* world, b2Vec2 position, b2Vec2 force );
			void addBody( b2World* world, b2Vec2 position, b2Vec2 size );
			void addBody ( b2Body* body );
			void addWall( b2World* world, float xPos, float yPos, float width, float height);
			void addChain( b2World* world, b2Vec2 vertices[], int length, float friction );
			void clearPhysics();

			///Does this character exist?
			bool exists(sf::Int8 clientID);

			// Getters
			/// Get list of all characters.
			std::vector<ICharacter*>* getCharacters(){ return &characters; }
			/// Get a specific character.
			ICharacter* getCharacter(int i){ return characters.at(i); }

			/// Get list of all bullets.
			std::vector<IBullet*>* getBullets(){ return &bullets; }
			int getBulletCount(){return bullets.size(); };
			std::vector<DynamicGameObject*>* getDeletionList() { return &deletionList; }
			/// Get list of all bodies.
			std::vector<b2Body*>* getBodies(){ return &bodies; }
			/// Get list of all world chains.
			std::vector<WorldChain*>* getChains(){ return &chains; }
			/// Get a specific world chains.
			WorldChain* getChain(int i){ return chains.at(i); }


			/// Get the character with the specific client ID
			ICharacter* getCharacter(sf::Int8 clientID);
			/// Get a specific bullet.
			IBullet* getBullet(int i){ return bullets.at(i); }
			/// Get a specific body.
			b2Body* getBody(int i){ return bodies.at(i); }

			//b2World* getb2World();

			/// Get logic fps.
			int getLogicFps(){ return logicFps; }

			void scheduleForDeletion(DynamicGameObject* object);
			void removeBullet(IBullet* bullet);
			void removeBulletsExcept(sf::Int8 clientID);

			// Setters
			// Set logic fps
			void setLogicFps(int fps){logicFps = fps;};

			/// Set the ID of the character belonging to the local player.
			void setCurrentCharacterId(int id) {currentCharacterId = id;}
			/// Get the ID of the character belonging to the local player.
			int getCurrentCharacterId() {return currentCharacterId;}

			virtual void notify(Event e, void* object);
			ICharacter* getCurrentCharacter() {return characters.at(currentCharacterId);}

			void setAsClient(){isClient = true;};
		private:
			int currentCharacterId;
			// Pointer to corresponding world object
			//World* world;
			// Vector containing bullets
			std::vector<IBullet*> bullets;
			// A queue, containing all bullets scheduled for deletion.
			std::vector<DynamicGameObject*> deletionList;
			// Vector containing characters
			std::vector<ICharacter*> characters;
			std::vector<WorldChain*> chains;
			// Vector containing generic Box2D bodies
			std::vector<b2Body*> bodies;

			// Variable for keeping track of logic thread fps
			int logicFps;

			bool isClient;
    };
}

#endif
