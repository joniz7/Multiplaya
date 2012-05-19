////////////////////////////////////////////////////////////
/// Bullet
////////////////////////////////////////////////////////////
#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <iostream>
#include <list>
#include <cmath>

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "../defines.h"
#include "GameObject.h"
#include "worlddata.h"

namespace mp
{
	class WorldData;

    class Bullet : public GameObject
    {
        public:
			Bullet( BulletType type, sf::Int8 owner, b2World* world, b2Vec2 position, b2Vec2 force, WorldData* worldData  );
            virtual ~Bullet();

			void explode();

			b2Vec2 getPosition(){return body->GetPosition();};
			b2BodyDef* getBodyDef(){return &bodyDef;};
			b2Body* getBody(){return body;};
			BulletType getType(){return type;};
			sf::Int8 getOwner(){return owner;};
			virtual void onCollision(GameObject* crashedWith);
			virtual void onNoCollision(GameObject* crashedWith) {};
			bool operator == (const Bullet* bullet);
        private:
			BulletType type;
			sf::Int8 owner;
			b2BodyDef bodyDef;
			b2Body* body;

			WorldData* worldData;
			b2World* world;

			bool scheduledForDeletion;
    };
}

#endif
