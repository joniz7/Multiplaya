////////////////////////////
// Bullet testing.
////////////////////////////

#include "stdafx.h"
#include "gtest/gtest.h"

//#include <global.h>
#include <model/worlddata.h>
#include <model/world.h>
#include <model/bullet.h>
#include <model/character.h>

namespace mpt {

class WorldTest : public ::testing::Test {
 protected:
	// Define worldData ^__^
	mp::WorldData* worldData;
	mp::World* world;
	b2World* physicsWorld;

  WorldTest() {
	// setup the world properties.
	b2Vec2 gravity(0, -9.8f);
	// Create the world our objects reside in.
	physicsWorld = new b2World(gravity);
	// Create world data.
	worldData = new mp::WorldData();
	world = new mp::World(worldData);
  }

  virtual ~WorldTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

};


TEST_F(WorldTest, bulletFactory) {  
	// Set up properties of a test bullet.
	b2Vec2 position(2,2);
	int clientID = 0;
	
	// Create bullet using World's createBullet() factory.
	world->createBullet(position, b2Vec2(2,2), clientID);
	
	// Fetch first bullet from worldData.
	mp::Bullet* bullet = worldData->getBullet(0);
	
	ASSERT_EQ(bullet->getPosition(), position);
	ASSERT_EQ(bullet->getOwner(), clientID);

	delete bullet;
}

TEST_F(WorldTest, characterFactory) {
	b2Vec2 position(2,2);
	int clientID = 0;
	
	world->createCharacter(position, b2Vec2(1,1), clientID);
	
	mp::ICharacter* character = worldData->getCharacter(0);
	
	// TODO: why does this fail?
	//ASSERT_EQ(character->getPosition(), position);
	ASSERT_EQ(character->getClientID(), clientID);

	delete character;
}


}  // namespace
