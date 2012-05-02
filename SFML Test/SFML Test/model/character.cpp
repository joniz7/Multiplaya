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
		this->objectType = character;
		this->worldData = worldData;
		this->world = world;
		this->characterBody = characterBody;
		this->isGrounded = true;
		this->walking = false;
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    Character::~Character()
    {

    }

	void Character::onCollision(GameObject* crashedWith)
	{

	}

	void Character::jump()
	{
		if (isGrounded) {
			characterBody->ApplyLinearImpulse( b2Vec2(0, 125), characterBody->GetPosition());
		}
	}

	void Character::primaryFire()
	{
		// TODO: calculate force, by using mouse position and character position.
		Bullet* bullet = new Bullet(BulletType::GENERIC_BULLET, 0 ,world, characterBody->GetPosition(), b2Vec2(-200, 0));
		worldData->addBullet(bullet);
	}
}