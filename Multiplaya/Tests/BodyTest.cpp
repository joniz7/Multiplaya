////////////////////////////
// Bullet testing.
////////////////////////////

#include "stdafx.h"
#include "gtest/gtest.h"

//#include <global.h>
#include <model/WorldData.h>

namespace mpt {

class BodyTest : public ::testing::Test {
 protected:
	// Define worldData ^__^
	mp::WorldData* worldData;
	b2World* physicsWorld;

	
  BodyTest() {
	// Setup the world properties.
	b2Vec2 gravity(0, -9.8f);
	// Create the world our objects reside in.
	physicsWorld = new b2World(gravity);
	// Create world data.
	worldData = new mp::WorldData();
  }

  virtual ~BodyTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

};


TEST_F(BodyTest, addBody)
{
	b2Vec2 position(0,0);
	// Duplicated code, should probably use code in addBody or something..
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* characterBody = physicsWorld->CreateBody(&bodyDef);
	b2Vec2 size(2,2);
	// Define a box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x, size.y);
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	// Override the default friction.
	fixtureDef.friction = 2.0f;
	// Set restitution
	fixtureDef.restitution = 0.0f;
	// Add the shape to the body.
	characterBody->CreateFixture(&fixtureDef);
	characterBody->SetFixedRotation(true);
	worldData->addBody( characterBody );

	ASSERT_EQ(characterBody, worldData->getBody(0));
}


}  // namespace
