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

#include "bullet.h"
#include "worlddata.h"

//Defines
#include "../defines.h"

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
			Character(WorldData* worldData, b2World* world, b2Vec2 position, b2Vec2 size, sf::Int8 clientID);
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
			short getHealthState();
			void setHealth(short health);

			short getKills()  { return kills; }
			short getDeaths() { return deaths; }

			short getClip() { return clip; }

			b2Body* getBody() { return characterBody; }
			void setGrounded(bool choice) { grounded = choice; }
			bool isGrounded() { return grounded; }

			bool isShooting();
			void shoot();
			
			bool isReloading();
			void reload();

			void setWalking(bool choice) { walking = choice; }
			bool isWalking() { return walking; }

			void setIsFacingRight(bool choice) { facingRight = choice; }
			bool isFacingRight() { return facingRight; }

			void setPosition(b2Vec2 position, float32 angle);
			void setLinVelocity(b2Vec2 velocity);

			b2Vec2 getPosition() {return characterBody->GetPosition();};
			float32 getAngle() {return characterBody->GetAngle();};
			b2Vec2 getLinVelocity() {return characterBody->GetLinearVelocity();};

			sf::Int8 getClientID(){return clientID;};

			virtual void onCollision(GameObject* crashedWith);
			virtual void onNoCollision(GameObject* crashedWith) {};

			void connectToServer();
        private:
			b2Body* characterBody;
			WorldData* worldData;
			b2World* world;
			sf::Clock* shootingTimer;
			sf::Clock* reloadTimer;

			short health;
			short maxHealth;
			short cooldown;
			short reloadTime;
			
			short clip;
			short clipSize;
			short kills;
			short deaths;

			bool facingRight;
			bool grounded;
			bool leftSideTouchWall;
			bool rightSideTouchWall;
			bool walking;

			sf::Int8 clientID;


		class CharacterFootSensor : public GameObject
		{
			public:
				//CharacterFootSensor(Character* character);
				CharacterFootSensor(bool& grounded);
				virtual ~CharacterFootSensor() {};
				virtual void onCollision(GameObject* crashedWith);
				virtual void onNoCollision(GameObject* crashedWith) {};

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
				virtual void onNoCollision(GameObject* crashedWith);

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
				virtual void onNoCollision(GameObject* crashedWith);

			private:
				//Character* characterObject;
				bool& rightSideTouchWall;
		};



    };
}

#endif
