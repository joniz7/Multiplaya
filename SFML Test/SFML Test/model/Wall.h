#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "GameObject.h"
#include <Box2D.h>
#include <iostream>

namespace mp
{
	class Wall : public GameObject
	{
		public:
			Wall(b2World* world, float xPos, float yPos, float width, float height);
			~Wall();
			virtual void onCollision(GameObject* crashedWith);
		private:
			b2Body* wallBody;
	};
}
#endif
