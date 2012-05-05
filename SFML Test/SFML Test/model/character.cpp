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
    Character::Character(WorldData* worldData, b2World* world, b2Vec2 position, b2Vec2 size)
    {
		this->objectType = character;
		this->worldData = worldData;
		this->world = world;
		this->grounded = true;
		this->walking = false;
		this->setHealth(100); // TODO should default value be defined elsewhere?
		this->cooldown = 100; // milliseconds in between shots.
		this->shootingTimer = new sf::Clock();

		// Duplicated code, should probably use code in addBody or something..
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x, position.y);
		this->characterBody = world->CreateBody(&bodyDef);

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


		// Test code
		//add foot sensor fixture
		dynamicBox.SetAsBox(0.3, 0.3, b2Vec2(0,-2), 0);
		fixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = characterBody->CreateFixture(&fixtureDef);
		footSensorFixture->SetUserData( new CharacterFootSensor( this ) );


    }

	Character::CharacterFootSensor::CharacterFootSensor(Character* character)
	{
		this->character = character;
		this->objectType = characterFootSensor;
	}

	Character::CharacterFootSensor::~CharacterFootSensor()
	{

	}

	void Character::CharacterFootSensor::onCollision(GameObject* crashedWith)
	{
		if ( crashedWith->objectType == wall)
		{
			std::cout << "wall" << std::endl;
			character->setGrounded(true);
		}
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
		std::cout << "Trying to jump" << std::endl;
		if (grounded) {
			characterBody->ApplyLinearImpulse( b2Vec2(0, 125), characterBody->GetPosition());
			setGrounded(false);
		} else
			std::cout << "Failed to jump WHY?!" << std::endl;
	}

	void Character::setShooting() {
		shootingTimer->restart();
	}
	bool Character::isShooting() {
		return (shootingTimer->getElapsedTime().asMilliseconds() < cooldown);
	}

	void Character::primaryFire()
	{
		if (isShooting()) { return; }
		else { setShooting(); }

		
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