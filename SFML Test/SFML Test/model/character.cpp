////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "character.h"

////////////////////////////////////////////////////////////
/// Character class. Holds data regarding character
/// position, activity etc..
/// Does NOT handle player input etc., see Player class for
/// that kind of stuff
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    Character::Character(WorldData* worldData, b2World* world, b2Body* characterBody)
    {
		this->worldData = worldData;
		this->world = world;
		this->characterBody = characterBody;
		this->isGrounded = true;
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    Character::~Character()
    {

    }

	void Character::jump()
	{
		if (isGrounded) {
			characterBody->ApplyLinearImpulse( b2Vec2(0, 75), characterBody->GetPosition());
		}
	}

	void Character::primaryFire()
	{
		//Fire, ugly code for testing shooting bullets, will be moved to method in character class
		Bullet* bullet = new Bullet(BulletType::GENERIC_BULLET, 0 ,world, b2Vec2(20, 30), b2Vec2(-200, 0));
		worldData->addBullet(bullet);
	}
}