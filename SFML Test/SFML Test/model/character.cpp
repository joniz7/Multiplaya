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
    Character::Character(WorldData* worldData, b2World* world, b2Vec2 position, b2Vec2 size, sf::Int8 clientID)
    {

		this->objectType = character;
		this->worldData = worldData;
		this->world = world;
		this->grounded = true;
		this->leftSideTouchWall = false;
		this->rightSideTouchWall = false;
		this->walking = false;
		this->maxHealth = 80;
		this->setHealth(50); // TODO should default value be defined elsewhere?
		this->cooldown = 100; // milliseconds in between shots.
		this->reloadTime = 1000; // Milliseconds it takes to reload.
		this->clipSize = 11; // Amount of bullets magazine holds.
		this->clip = clipSize; // Begin game fully loaded.

		this->kills  = 0;// Kill stat.
		this->deaths = 0;// Death stat.

		this->clientID = clientID;

		this->shootingTimer = new sf::Clock();
		this->reloadTimer = new sf::Clock();

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
		footSensorFixture->SetUserData( new CharacterFootSensor( grounded ) );

		//add left sensor fixture
		dynamicBox.SetAsBox(0.1, 1, b2Vec2(1, 0), 0);
		fixtureDef.isSensor = true;
		b2Fixture* leftSensorFixture = characterBody->CreateFixture(&fixtureDef);
		leftSensorFixture->SetUserData( new CharacterLeftSensor( leftSideTouchWall ) );


		//add right sensor fixture
		dynamicBox.SetAsBox(0.1, 1, b2Vec2(-1.2, 0), 0);
		fixtureDef.isSensor = true;
		b2Fixture* rightSensorFixture = characterBody->CreateFixture(&fixtureDef);
		rightSensorFixture->SetUserData( new CharacterRightSensor( rightSideTouchWall) );


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
		if ( grounded ) {
			characterBody->ApplyLinearImpulse( b2Vec2(0, 200), characterBody->GetPosition());
			setGrounded(false);
		}
		else if ( leftSideTouchWall )
		{
			characterBody->ApplyLinearImpulse( b2Vec2( -250, 300), characterBody->GetPosition());
			leftSideTouchWall = false;
		}
		else if ( rightSideTouchWall )
		{
			characterBody->ApplyLinearImpulse( b2Vec2( 250, 300), characterBody->GetPosition());
			rightSideTouchWall = false;
		}
	}

	void Character::shoot() {
		if (--clip <= 0) {
			this->reload();
		}
		else {
			shootingTimer->restart();
		}
	}
	bool Character::isShooting() {
		return (shootingTimer->getElapsedTime().asMilliseconds() < cooldown);
	}

	void Character::reload() {
		// Fill our magazine.
		this->clip = clipSize;
		// Force the user to wait >:)
		reloadTimer->restart();
	}
	bool Character::isReloading() {
		return (reloadTimer->getElapsedTime().asMilliseconds() < reloadTime);
	}

	void Character::primaryFire()
	{
		if (isReloading()) { return; }
		if (isShooting()) { return; }
		else { shoot(); }

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
		Bullet* bullet = new Bullet(GENERIC_BULLET, 0 ,world, gunPosition, force, worldData);
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
		else if (health>maxHealth) {
			this->health = maxHealth;
		}
		else {
			this->health = health;
		}
		std::cout << "health: " << this->health << std::endl;
	}
	/////////////////////////////////////
	/// Returns the character's health level.
	/// \return a number between 0 and 8.
	/////////////////////////////////////
	short Character::getHealthState() {
		int result = (health/10);
		if ((result == 0) && health>0) {
			result = 1;
		}
		return result;
	}

	void Character::kill() {
		std::cout << "I'm a dead character. FML" << std::endl;
	}

	void Character::connectToServer() {
		worldData->notify(CONNECT_SERVER , 0);
	}

	//Foot sensor
	Character::CharacterFootSensor::CharacterFootSensor(bool& grounded) : grounded(grounded) {
		this->objectType = characterFootSensor;
	}
	void Character::CharacterFootSensor::onCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall) {
			grounded = true;
		}
	}

	// Leftside
	Character::CharacterLeftSensor::CharacterLeftSensor(bool& leftSideTouchWall) : leftSideTouchWall(leftSideTouchWall)	{
		this->objectType = characterLeftSensor;
	}
	void Character::CharacterLeftSensor::onCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall){
			leftSideTouchWall = true;
		}
	}
	void Character::CharacterLeftSensor::onNoCollision(GameObject* crashedWith) {
		leftSideTouchWall = false;
	}

	// Rightside
	Character::CharacterRightSensor::CharacterRightSensor(bool& rightSideTouchWall) : rightSideTouchWall(rightSideTouchWall) {
		this->objectType = characterRightSensor;
	}
	void Character::CharacterRightSensor::onCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall) {
			rightSideTouchWall = true;
		}
	}
	void Character::CharacterRightSensor::onNoCollision(GameObject* crashedWith) {
		rightSideTouchWall = false;
	}


	void Character::setPosition(b2Vec2 position, float32 angle)
	{
		characterBody->SetTransform(position, angle);
	}

	void Character::setLinVelocity(b2Vec2 velocity)
	{
		characterBody->SetLinearVelocity(velocity);
	}
}
