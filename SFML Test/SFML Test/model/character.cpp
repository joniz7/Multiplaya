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
		this->grounded = true;
		this->shooting = false;
		this->walking = false;
		this->setHealth(100); // TODO should default value be defined elsewhere?
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    Character::~Character()
    {

    }

	////////////////////////////////////////////////////////////
	// Called when colliding with something.
	////////////////////////////////////////////////////////////
	void Character::onCollision(GameObject* crashedWith)
	{
		// If we collided with bullet, take damage.
		if (crashedWith->objectType == bullet) {
			std::cout << "Collision: Character <-> bullet" << std::endl;
			Bullet* b = static_cast<Bullet*>( crashedWith );
			inflictDamage(b);
		}
		// No other checks neccessary?	
	}

	void Character::jump()
	{
		if (grounded) {
			characterBody->ApplyLinearImpulse( b2Vec2(0, 125), characterBody->GetPosition());
		}
	}

	void Character::primaryFire()
	{
		if (shooting) { return; }
		else {shooting = true;}
		
		int speed = 800;
		b2Vec2 charPos = characterBody->GetPosition();
		b2Vec2 charSpeed = characterBody->GetLinearVelocity();
		b2Vec2 mousePos = worldData->getMousePosition();
		
		// We're just about to calculate these two vectors.
		b2Vec2 gunPosition; // Where the bullet should be placed.
		b2Vec2 force;		// The initial force of the bullet.
		
		// Direction the bullet should fly in.
		force = charPos - mousePos;
		force.Normalize();
		gunPosition = force;
		// Apply speed factor and characer's speed to our force vector.
		force.Set((force.x * speed)+charSpeed.x, -((force.y * speed)+charSpeed.y)); 
		// Bullet spawning point should be relative to char.
		gunPosition.Set(charPos.x-gunPosition.x, gunPosition.y + charPos.y);
		
		// TODO: bullet spawning point is not perfect.

		// Create bullet, and add to world.
		Bullet* bullet = new Bullet(BulletType::GENERIC_BULLET, 0 ,world, gunPosition, force, worldData);
		worldData->addBullet(bullet);

		shooting = false;
	}

	/////////////////////////////////////////////////
	// Inflicts damage, based on the supplied bullet.
	/////////////////////////////////////////////////
	void Character::inflictDamage(Bullet* b) {
		// Should different kinds of bullets inflict different damage?
		short damage = 10;

		short hp = this->getHealth();
		hp -= damage;
		this->setHealth(hp);
	}

	/////////////////////////////////////
	// Changes the character's health.
	// If health<1, kills the character.
	/////////////////////////////////////
	void Character::setHealth(short health) {
		// Die if HP drops below 1.
		if (health < 1) {
			this->kill();
		}
		// Should we enforce maxHP here?
		else {
			this->health = health;
		}
		std::cout << "health: " << this->health << std::endl;
	}
	
	void Character::kill()
	{
		std::cout << "I'm a dead character. FML" << std::endl;
	}
}