////////////////////////////
// Bullet testing.
////////////////////////////

#include "stdafx.h"
#include "gtest/gtest.h"

//#include <global.h>
#include <model/WorldData.h>


namespace mpt {

class BulletTest : public ::testing::Test {
 protected:
	// Define worldData ^__^
	mp::WorldData* worldData;
	b2World* physicsWorld;

	std::vector<mp::IBullet*> testBullets;

  BulletTest() {
	// Setup the world properties.
	b2Vec2 gravity(0, -9.8f);
	// Create the world our objects reside in.
	physicsWorld = new b2World(gravity);
	// Create world data.
	worldData = new mp::WorldData();

	// Create generic bullets, owner ID 0.
	testBullets.push_back( new mp::StandardBullet(0 , physicsWorld, b2Vec2(10, 10), b2Vec2(-50, 0)) );
	testBullets.push_back( new mp::StandardBullet(0, physicsWorld, b2Vec2(10, 10), b2Vec2(-50, 0)) );
	// Create generic bullets, owner ID 1.
	testBullets.push_back( new mp::StandardBullet(1, physicsWorld, b2Vec2(20, 20), b2Vec2(-40, 0)) );
	testBullets.push_back( new mp::StandardBullet(1, physicsWorld, b2Vec2(30, 30) , b2Vec2(40, 0))  );
  }

  virtual ~BulletTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

};


TEST_F(BulletTest, bullet_comparisons)
{	
	// A bullet should be equal itself.
	ASSERT_EQ(testBullets.at(0)->getBody(), testBullets.at(0)->getBody());
	ASSERT_EQ(testBullets.at(0)->getOwner(), testBullets.at(0)->getOwner());
	ASSERT_EQ(testBullets.at(0)->getPosition(), testBullets.at(0)->getPosition());

}

TEST_F(BulletTest, bullet_addition)
{
	// Add all our test bullets to world.	
	for(unsigned int i=0;i<testBullets.size(); i++) {
		worldData->addBullet(testBullets.at(i));
	}
	
	// Compare previously created bullet with the one returned from getBullet().
	for(unsigned int i=0;i<testBullets.size(); i++) {
		ASSERT_EQ(testBullets.at(i)->getBody(), worldData->getBullet(i)->getBody());
		ASSERT_EQ(testBullets.at(i)->getOwner(), worldData->getBullet(i)->getOwner());
		ASSERT_EQ(testBullets.at(i)->getPosition(), worldData->getBullet(i)->getPosition());
	}

	// We have added 4 bullets, so size should be 4.
	int size = worldData->getBullets()->size();
	ASSERT_EQ(testBullets.size(), size);
	
}


}  // namespace
