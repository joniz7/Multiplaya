#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <iostream>
#include <list>
#include <cmath>

#include <SFML/System.hpp>
#include "../IBullet.h"

namespace mp
{
	/**
	 * A class representing a regular bullet.
	 */
    class StandardBullet : public IBullet
    {
        public:
			StandardBullet( sf::Int8 owner, b2World* world, b2Vec2 position, b2Vec2 force );
            virtual ~StandardBullet();

			void explode();

			virtual void onCollision(GameObject* crashedWith);
			virtual void onNoCollision(GameObject* crashedWith) {};
			bool operator == (const IBullet* bullet);
		protected:
			StandardBullet();

    };
}

#endif
