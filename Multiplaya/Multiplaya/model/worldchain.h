#ifndef WORLDCHAIN_H_INCLUDED
#define WORLDCHAIN_H_INCLUDED

#include "GameObject.h"
#include <Box2D.h>
#include <iostream>
#include <vector>

namespace mp
{
	class WorldChain : public GameObject
	{
		public:
			WorldChain(b2World* world, b2Vec2 vertices[], int length, float friction);
			~WorldChain();
			virtual void onCollision(GameObject* crashedWith);
			virtual void onNoCollision(GameObject* crashedWith){}
			std::vector<b2Vec2>* getVertices(){ return &verticeList; }
		private:
			b2World* world;
			b2Body* chainBody;
			std::vector<b2Vec2> verticeList;
	};
}
#endif
