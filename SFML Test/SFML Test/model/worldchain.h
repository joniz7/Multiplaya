#ifndef WORLDCHAIN_H_INCLUDED
#define WORLDCHAIN_H_INCLUDED

#include "GameObject.h"
#include <Box2D.h>
#include <iostream>

namespace mp
{
	class WorldChain : public GameObject
	{
		public:
			WorldChain(b2World* world, b2Vec2 vertices[], int length, float friction);
			~WorldChain();
			virtual void onCollision(GameObject* crashedWith);
			virtual void onNoCollision(GameObject* crashedWith) {};
		private:
			b2World* world;
			b2Body* chainBody;
	};
}
#endif
