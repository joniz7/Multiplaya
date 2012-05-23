#ifndef IBULLET_H_INCLUDED
#define IBULLET_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <iostream>
#include <list>
#include <cmath>

#include <SFML/System.hpp>
#include "DynamicGameObject.h"

namespace mp
{
	/**
	 * An interface representing a bullet.
	 */
    class IBullet : public DynamicGameObject
    {
        public:
			virtual void explode() = 0;

			// Getters
			sf::Int8 getOwner(){ return owner;  }
			short getDamage()  { return damage; }
			b2Vec2 getInitForce(){return initialForce;}

			virtual void onCollision(GameObject* crashedWith) = 0;
			virtual void onNoCollision(GameObject* crashedWith) = 0;
			bool operator == (const IBullet* b) {return b == this; }
			
		protected:
			IBullet() {}
			short damage;
			sf::Int8 owner;
			b2BodyDef bodyDef;
			b2Vec2 initialForce;
    };
}

#endif
