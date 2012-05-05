#include "Wall.h"

namespace mp 
{
	Wall::Wall(b2World* world, float xPos, float yPos, float width, float height)
	{
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(xPos, yPos);

		b2Body* groundBody = world->CreateBody(&groundBodyDef);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(width, height);
		
		b2Fixture* testFixture = groundBody->CreateFixture(&groundBox, 0.0f);
		testFixture->SetUserData(this);
		
		this->wallBody = wallBody;
		this->objectType = wall;
	}

	void Wall::onCollision(GameObject* crashedWith)
	{
		if (crashedWith->objectType != wall) {
			//std::cout << "Collision: wall <-> ?" << std::endl;
		}
	}

	Wall::~Wall()
	{
	}
}
