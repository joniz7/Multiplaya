////////////////////////////
// Bullet testing.
////////////////////////////

#include "stdafx.h"
#include "gtest/gtest.h"

//#include <global.h>
#include <sfml.h>
#include <model/worlddata.h>
#include <model/Player.h>

namespace mpt {

class BulletTest : public ::testing::Test {
 protected:
	// Define worldData ^__^
	mp::WorldData* worldData;
	b2World* physicsWorld;

	mp::Bullet* testBullet01;
	mp::Bullet* testBullet02;
	mp::Bullet* testBullet11;
	mp::Bullet* testBullet12;

  BulletTest() {
	// Setup the world properties.
	b2Vec2 gravity(0, -9.8f);
	// Create the world our objects reside in.
	physicsWorld = new b2World(gravity);
	// Create world data.
	worldData = new mp::WorldData();
  }

  virtual ~BulletTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

};


TEST_F(BulletTest, bullet_creation)
{
	// Create generic bullets, owner ID 0.
	testBullet01 = new mp::Bullet(BulletType::GENERIC_BULLET,0,physicsWorld,b2Vec2(10,10),b2Vec2(-50,0));
	testBullet02 = new mp::Bullet(BulletType::GENERIC_BULLET,0,physicsWorld,b2Vec2(10,10),b2Vec2(-50,0));
	// Create generic bullets, owner ID 1.
	testBullet11 = new mp::Bullet(BulletType::GENERIC_BULLET,1,physicsWorld,b2Vec2(20,20),b2Vec2(-40,0));
	testBullet12 = new mp::Bullet(BulletType::GENERIC_BULLET,1,physicsWorld,b2Vec2(30,30),b2Vec2(40,0));
	
	// A bullet should be equal itself.
	ASSERT_EQ(&testBullet01, &testBullet01);
	// Two bullets should differ, even though they share all attributes.
	ASSERT_NE(&testBullet01, &testBullet02);
}

TEST_F(BulletTest, bullet_addition)
{
	
	// Add our 4 bullets to the world.

	/* TODO: addBullet() results in "unknown file: error: SEH exception". whyyy?
	*/
	worldData->addBullet(testBullet01);
	worldData->addBullet(testBullet02);
	worldData->addBullet(testBullet11);
	worldData->addBullet(testBullet12);
	

	// TODO: Compare previously created bullet with the one returned from getBullet().
	// EXPECT_EQ((&testBullet0_1), &(worldData->getBullet(0)));
	// Repeat for all 4 bullets.


	
	// We have added 4 bullets, so size should be 4.
	int size = worldData->getBltVec()->size();
	ASSERT_EQ(4, size);
	
}


}  // namespace
