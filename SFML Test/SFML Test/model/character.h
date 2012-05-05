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
			Character(WorldData* worldData, b2World* world, b2Body* characterBody);
            ~Character();
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

			bool isShooting() { return shooting; }

			void setWalking(bool choice) { walking = choice; }
			bool isWalking() { return walking; }

			void setIsFacingRight(bool choice) { facingRight = choice; }
			bool isFacingRight() { return facingRight; }

			virtual void onCollision(GameObject* crashedWith);
        private:
			b2Body* characterBody;
			WorldData* worldData;
			b2World* world;

			short health;

			bool facingRight;
			bool grounded;
			bool shooting;
			bool walking;
			
    };
}

#endif