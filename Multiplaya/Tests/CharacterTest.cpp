////////////////////////////
// Bullet testing.
////////////////////////////

#include "stdafx.h"
#include "gtest/gtest.h"

//#include <global.h>
#include <model/WorldData.h>
#include "model/ICharacter.h"

namespace mpt {

class CharacterTest : public ::testing::Test {
 protected:
	// Define worldData ^__^
	mp::WorldData* worldData;
	b2World* physicsWorld;

	std::vector<mp::ICharacter*> testCharacters;

  CharacterTest() {
	// Setup the world properties.
	b2Vec2 gravity(0, -9.8f);
	// Create the world our objects reside in.
	physicsWorld = new b2World(gravity);
	// Create world data.
	worldData = new mp::WorldData();

	testCharacters.push_back( new mp::DefaultCharacter(physicsWorld, b2Vec2(2.0f,2.0f), b2Vec2(1.0f,1.0f), 0) );
	testCharacters.push_back( new mp::DefaultCharacter(physicsWorld, b2Vec2(4.0f,2.0f), b2Vec2(1.0f,1.0f), 1) );

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
	for(unsigned int i = 0; i < testCharacters.size(); i++) {
		worldData->addCharacter(testCharacters.at(i));
	}
	
	// Compare previously created character with the one returned from getCharacter().
	for(unsigned int i = 0; i < testCharacters.size(); i++) {
		ASSERT_EQ(testCharacters.at(i)->getBody(), worldData->getCharacter((int) i)->getBody());
		ASSERT_EQ(testCharacters.at(i)->getClientID(), worldData->getCharacter((int) i)->getClientID());
		ASSERT_EQ(testCharacters.at(i)->getClip(), worldData->getCharacter((int) i)->getClip());
		ASSERT_EQ(testCharacters.at(i)->getDeaths(), worldData->getCharacter((int) i)->getDeaths());
		ASSERT_EQ(testCharacters.at(i)->getHealth(), worldData->getCharacter((int) i)->getHealth());
		ASSERT_EQ(testCharacters.at(i)->getHealthState(), worldData->getCharacter((int) i)->getHealthState());
		ASSERT_EQ(testCharacters.at(i)->getKills(), worldData->getCharacter((int) i)->getKills());
		ASSERT_EQ(testCharacters.at(i)->getLinVelocity(), worldData->getCharacter((int) i)->getLinVelocity());
		ASSERT_EQ(testCharacters.at(i)->getPosition(), worldData->getCharacter((int) i)->getPosition());
		ASSERT_EQ(testCharacters.at(i)->isFacingLeft(), worldData->getCharacter((int) i)->isFacingLeft());
		ASSERT_EQ(testCharacters.at(i)->isGrounded(), worldData->getCharacter((int) i)->isGrounded());
		ASSERT_EQ(testCharacters.at(i)->isReloading(), worldData->getCharacter((int) i)->isReloading());
		ASSERT_EQ(testCharacters.at(i)->isShooting(), worldData->getCharacter((int) i)->isShooting());
		ASSERT_EQ(testCharacters.at(i)->isWalking(), worldData->getCharacter((int) i)->isWalking());
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
	for(unsigned int i=0;i<testCharacters.size(); i++) {
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
