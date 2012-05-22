////////////////////////////
// Bullet testing.
////////////////////////////

#include "stdafx.h"
#include "gtest/gtest.h"

//#include <global.h>
#include <model/worlddata.h>

namespace mpt {

class CharacterTest : public ::testing::Test {
 protected:
	// Define worldData ^__^
	mp::WorldData* worldData;
	b2World* physicsWorld;

	std::vector<mp::Character*> testCharacters;

  CharacterTest() {
	// Setup the world properties.
	b2Vec2 gravity(0, -9.8f);
	// Create the world our objects reside in.
	physicsWorld = new b2World(gravity);
	// Create world data.
	worldData = new mp::WorldData();

	testCharacters.push_back( new mp::Character(physicsWorld, b2Vec2(2.0f,2.0f), b2Vec2(1.0f,1.0f), 0) );
	testCharacters.push_back( new mp::Character(physicsWorld, b2Vec2(4.0f,2.0f), b2Vec2(1.0f,1.0f), 1) );

  }

  virtual ~CharacterTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

};


TEST_F(CharacterTest, character_comparisons)
{	
	// A character should be equal itself.
	ASSERT_EQ(testCharacters.at(0)->getBody(), testCharacters.at(0)->getBody());
	ASSERT_EQ(testCharacters.at(0)->getLinVelocity(), testCharacters.at(0)->getLinVelocity());
	ASSERT_EQ(testCharacters.at(0)->getPosition(), testCharacters.at(0)->getPosition());
	
}

TEST_F(CharacterTest, character_addition)
{
	// Add all our test characters to world.	
	for(int i = 0; i < testCharacters.size(); i++) {
		worldData->addCharacter(testCharacters.at(i));
	}
	
	// Compare previously created character with the one returned from getCharacter().
	for(int i = 0; i < testCharacters.size(); i++) {
		ASSERT_EQ(testCharacters.at(i)->getBody(), worldData->getCharacter(i)->getBody());
		ASSERT_EQ(testCharacters.at(i)->getClientID(), worldData->getCharacter(i)->getClientID());
		ASSERT_EQ(testCharacters.at(i)->getClip(), worldData->getCharacter(i)->getClip());
		ASSERT_EQ(testCharacters.at(i)->getDeaths(), worldData->getCharacter(i)->getDeaths());
		ASSERT_EQ(testCharacters.at(i)->getHealth(), worldData->getCharacter(i)->getHealth());
		ASSERT_EQ(testCharacters.at(i)->getHealthState(), worldData->getCharacter(i)->getHealthState());
		ASSERT_EQ(testCharacters.at(i)->getKills(), worldData->getCharacter(i)->getKills());
		ASSERT_EQ(testCharacters.at(i)->getLinVelocity(), worldData->getCharacter(i)->getLinVelocity());
		ASSERT_EQ(testCharacters.at(i)->getPosition(), worldData->getCharacter(i)->getPosition());
		ASSERT_EQ(testCharacters.at(i)->isFacingLeft(), worldData->getCharacter(i)->isFacingLeft());
		ASSERT_EQ(testCharacters.at(i)->isGrounded(), worldData->getCharacter(i)->isGrounded());
		ASSERT_EQ(testCharacters.at(i)->isReloading(), worldData->getCharacter(i)->isReloading());
		ASSERT_EQ(testCharacters.at(i)->isShooting(), worldData->getCharacter(i)->isShooting());
		ASSERT_EQ(testCharacters.at(i)->isWalking(), worldData->getCharacter(i)->isWalking());
	}

	// We have added 2 characters, so size should be 2.
	int size = worldData->getCharacters()->size();
	ASSERT_EQ(testCharacters.size(), size);
	
}

////////////////////////////////////
/// Test our Characters' actions.
/// Tries to fire, reload, and jump.
////////////////////////////////////
TEST_F(CharacterTest, character_actions)
{
	
	for(int i=0;i<testCharacters.size(); i++) {
		testCharacters.at(i)->reload();
		ASSERT_EQ(testCharacters.at(i)->isReloading(), true);

		testCharacters.at(i)->primaryFire(b2Vec2(0,0));
		ASSERT_EQ(testCharacters.at(i)->isShooting(), true);
		
		testCharacters.at(i)->jump();
		ASSERT_EQ(testCharacters.at(i)->isGrounded(), false);
	}
}

////////////////////////////////////
/// Test our Characters' setters.
////////////////////////////////////
TEST_F(CharacterTest, character_setters)
{
	for(int i=0;i<testCharacters.size(); i++) {
		testCharacters.at(i)->setIsFacingLeft(true);
		ASSERT_EQ(testCharacters.at(i)->isFacingLeft(), true);
		
		testCharacters.at(i)->setGrounded(false);
		ASSERT_EQ(testCharacters.at(i)->isGrounded(), false);
		
		testCharacters.at(i)->setWalking(true);
		ASSERT_EQ(testCharacters.at(i)->isWalking(), true);
		
		testCharacters.at(i)->setLinVelocity(b2Vec2(5,5));
		ASSERT_EQ(testCharacters.at(i)->getLinVelocity(), b2Vec2(5,5));
		
		testCharacters.at(i)->setPosition(b2Vec2(-5,5),5);
		ASSERT_EQ(testCharacters.at(i)->getPosition(), b2Vec2(-5,5));
	}
}


}  // namespace
