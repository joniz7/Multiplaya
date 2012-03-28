////////////////////////////////////////////////////////////
/// Bullet
////////////////////////////////////////////////////////////
#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>

// SFML specific headers
#include "../sfml.h"

// Box2D specific headers
#include <Box2D.h>

namespace mp
{
    class Bullet
    {
        public:
			Bullet( b2World* world, b2Vec2 position, b2Vec2 force  );
            ~Bullet();
			b2Vec2 getPosition();
			b2BodyDef* getBodyDef();
			b2Body* getBody();
        private:
			b2BodyDef bodyDef;
			b2Body* body;

			
    };
}

#endif
