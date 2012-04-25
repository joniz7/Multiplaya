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

//Defines
#include "defines.h"

namespace mp
{
    class Character
    {
        public:
			Character(b2Body* characterBody);
            ~Character();
			void jump();
			void crouch();
			void primaryFire();
			void secondaryFire();
			void kill();
			void setInvincible(float duration);
			void setMovement(int direction);
			short getHealth() { return health; };
			void setHealth(short health) { this->health = health; }
			b2Body* getBody() { return characterBody; }
			void setGrounded(bool choice) { isGrounded = choice; } 
        private:
			bool facingRight;
			short health;
			bool isGrounded;
			b2Body* characterBody;
    };
}

#endif