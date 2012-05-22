#include "Wall.h"

namespace mp
{
	/**
	 * Create a new wall.
	 *
	 * @param world - the physics world we should inhabit.
	 * @param xPos - Where we should be located, x-wise.
	 * @param yPos - where we should be located, y-wise.
	 * @param width - the width of the wall.
	 * @param height - the height of the wall.
	 */
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

	/**
	 * Destructor
	 */
	Wall::~Wall() {}

}
