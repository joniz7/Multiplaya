#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

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
	class WorldData;

	/**
	 * A class representing a bullet.
	 */
    class Bullet : public DynamicGameObject
    {
        public:
			Bullet( sf::Int8 owner, b2World* world, b2Vec2 position, b2Vec2 force );
            virtual ~Bullet();

			void explode();

			sf::Int8 getOwner(){return owner;};
			virtual void onCollision(GameObject* crashedWith);
			virtual void onNoCollision(GameObject* crashedWith) {};
			bool operator == (const Bullet* bullet);
        private:

			sf::Int8 owner;
			b2BodyDef bodyDef;

    };
}

#endif
