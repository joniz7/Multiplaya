////////////////////////////////////////////////////////////
/// World chain class. Represents a segment of lines that
/// acts as world physics.
////////////////////////////////////////////////////////////
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
			// Returns a vector of all the vertices in the chain for drawing etc.
			std::vector<b2Vec2>* getVertices(){ return &verticeList; }
		private:
			std::vector<b2Vec2> verticeList;
	};
}
#endif
