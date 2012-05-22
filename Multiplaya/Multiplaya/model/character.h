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

#include "ICharacter.h"

#include "../services/resourcehandler.h"

namespace mp
{
    class Character : public ICharacter
    {
        public:
			Character(b2World* world, b2Vec2 pos, b2Vec2 size, sf::Int8 clientID);
            virtual ~Character();

			void update();
			void jump();

			void moveLeft();
			void moveRight();
			void moveUp();
			void moveDown();
			
			void crouch() {};
			void primaryFire(b2Vec2 &targetPos);
			void secondaryFire() {}
			void inflictDamage(Bullet* b);
			void kill();
			void setInvincible(float duration) {}
			void setMovement(int direction) {}

			short getHealth() { return health; };
			short getHealthState();
			void setHealth(short health);

			short getKills()  { return kills; }
			short getDeaths() { return deaths; }

			short getClip() { return clip; }

			void setGrounded(bool choice) { grounded = choice; }
			bool isGrounded() { return grounded; }

			bool isShooting();
			void shoot();
			
			bool isReloading();
			void reload();

			void setWalking(bool choice) { walking = choice; }
			bool isWalking() { return walking; }

			void setIsFacingLeft(bool choice) { facingLeft = choice; }
			bool isFacingLeft() { return facingLeft; }

			void setPosition(b2Vec2 position, float32 angle);
			void setLinVelocity(b2Vec2 velocity);

			void setTouchingWallLeft(bool choice){ leftSideTouchWall = choice; }
			bool isTouchingWallLeft(){ return leftSideTouchWall; }

			void isTouchingWallRight(bool choice){ rightSideTouchWall = choice; }
			bool isTouchingWallRight(){ return rightSideTouchWall; }

			void setWallSliding(bool wS){wallSliding = wS;}
			bool isWallSliding(){ return wallSliding; }

			void setFlipping(bool choice){ flipping = choice; }
			bool isFlipping(){return flipping;}

			void setFocusing(bool choice){ focusing = choice; }
			bool isFocusing(){ return focusing; }

			sf::Int8 getClientID(){ return clientID; } 
			void setClientID(sf::Int8 ID) { clientID = ID; }

			virtual void onCollision(GameObject* crashedWith);
			virtual void onNoCollision(GameObject* crashedWith) {}

			void connectToServer();

        private:

			
			void moveY(bool left);
			void moveX(bool left);

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

			bool focusing;
			bool facingLeft;
			bool grounded;
			bool leftSideTouchWall;
			bool rightSideTouchWall;
			bool walking;
			bool wallSliding;
			bool flipping;

			sf::Sound soundFire;
			sf::Sound soundReload;

			sf::Int8 clientID;


		class CharacterFootSensor : public GameObject
		{
			public:
				//CharacterFootSensor(Character* character);
				CharacterFootSensor(bool& grounded, bool& isFlipping);
				virtual ~CharacterFootSensor() {};
				virtual void onCollision(GameObject* crashedWith);
				virtual void onNoCollision(GameObject* crashedWith);

			private:
				//Character* characterObject;
				bool& grounded;
				bool& isFlipping;
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
