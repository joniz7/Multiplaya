////////////////////////////////////////////////////////////
/// Character class. Holds data regarding character
/// position, activity etc..
/// Does NOT handle player input etc., see Player class for
/// that kind of stuff
////////////////////////////////////////////////////////////
#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>

// Box2D specific headers
#include <Box2D.h>

#include "model/bullet.h"
#include "worlddata.h"

//Defines
#include "defines.h"

#include "../util/Observable.h"

#include "GameObject.h"

namespace mp
{
	// Forward class declarations.
	class Bullet;
	class WorldData;

    class Character : public GameObject
    {
        public:
			Character(WorldData* worldData, b2World* world, b2Vec2 position, b2Vec2 size);
            virtual ~Character();
			void jump();
			void crouch();
			void primaryFire();
			void secondaryFire();
			void inflictDamage(Bullet* b);
			void kill();
			void setInvincible(float duration);
			void setMovement(int direction);
			
			short getHealth() { return health; };
			void setHealth(short health);

			b2Body* getBody() { return characterBody; }
			void setGrounded(bool choice) { grounded = choice; } 
			bool isGrounded() { return grounded; } 

			bool isShooting();
			void setShooting();

			void setWalking(bool choice) { walking = choice; }
			bool isWalking() { return walking; }

			void setIsFacingRight(bool choice) { facingRight = choice; }
			bool isFacingRight() { return facingRight; }

			virtual void onCollision(GameObject* crashedWith);
        private:
			b2Body* characterBody;
			WorldData* worldData;
			b2World* world;
			sf::Clock* shootingTimer;

			short health;
			short cooldown;

			bool facingRight;
			bool grounded;
			bool leftSideTouchWall;
			bool rightSideTouchWall;
			bool walking;


		class CharacterFootSensor : public GameObject
		{
			public:
				//CharacterFootSensor(Character* character);
				CharacterFootSensor(bool& grounded);
				virtual ~CharacterFootSensor() {};
				virtual void onCollision(GameObject* crashedWith);
			
			private:
				//Character* characterObject;	
				bool& grounded;
		};

		class CharacterLeftSensor : public GameObject
		{
			public:
				//CharacterFootSensor(Character* character);
				CharacterLeftSensor(bool& leftSideTouchWall);
				virtual ~CharacterLeftSensor() {};
				virtual void onCollision(GameObject* crashedWith);
			
			private:
				//Character* characterObject;	
				bool& leftSideTouchWall;
		};

		class CharacterRightSensor : public GameObject
		{
			public:
				//CharacterFootSensor(Character* character);
				CharacterRightSensor(bool& rightSideTouchWall);
				virtual ~CharacterRightSensor() {};
				virtual void onCollision(GameObject* crashedWith);
			
			private:
				//Character* characterObject;	
				bool& rightSideTouchWall;
		};


			
    };
}

#endif