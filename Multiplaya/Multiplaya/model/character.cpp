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
    Character::Character(b2World* world, b2Vec2 pos, b2Vec2 size, sf::Int8 clientID)
    {
		this->world = world;

		this->objectType = character;
		this->grounded = false;
		this->leftSideTouchWall = false;
		this->rightSideTouchWall = false;
		this->walking = false;
		this->maxHealth = 80;
		this->setHealth(50); // TODO should default value be defined elsewhere?
		this->cooldown = 100; // milliseconds in between shots.
		this->reloadTime = 1000; // Milliseconds it takes to reload.
		this->clipSize = 11; // Amount of bullets magazine holds.
		this->clip = clipSize; // Begin game fully loaded.
		this->wallSliding = false;
		this->flipping = false;
		this->facingLeft = true;

		this->kills  = 0;// Kill stat.
		this->deaths = 0;// Death stat.

		this->clientID = clientID;

		this->shootingTimer = new sf::Clock();
		this->reloadTimer = new sf::Clock();

		// Duplicated code, should probably use code in addBody or something..
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		bodyDef.position.Set(pos.x, pos.y);
		b2Body* characterBody = world->CreateBody(&bodyDef);

		this->characterBody = characterBody;
		// Define a box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(size.x, size.y);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		// Override the default friction.
		fixtureDef.friction = 0.0f;
		// Set restitution
		fixtureDef.restitution = 0.0f;

		// Calculate unique identifying bits for this player.
		// (This makes us not collide with our own bullets)
		const short playerBits = short(pow(2.0, clientID + 1));
		fixtureDef.filter.categoryBits = playerBits;
		fixtureDef.filter.maskBits = 0xFFFF & (~playerBits);

		// Add the shape to the body.
		b2Fixture* characterBodyFixture = characterBody->CreateFixture(&fixtureDef);
		characterBodyFixture->SetUserData( this );
		characterBody->SetFixedRotation(true);
		// Test code
		//add foot sensor fixture
		dynamicBox.SetAsBox(0.3f, 0.3f, b2Vec2(0,-2), 0);

		fixtureDef.isSensor = true;

		b2Fixture* footSensorFixture = characterBody->CreateFixture(&fixtureDef);
		footSensorFixture->SetUserData( new CharacterFootSensor( grounded, flipping ) );

		//add left sensor fixture
		dynamicBox.SetAsBox(0.1f, 1, b2Vec2(1, 0), 0);
		fixtureDef.isSensor = true;
		b2Fixture* leftSensorFixture = characterBody->CreateFixture(&fixtureDef);
		leftSensorFixture->SetUserData( new CharacterLeftSensor( leftSideTouchWall ) );

		//add right sensor fixture
		dynamicBox.SetAsBox(0.1f, 1, b2Vec2(-1.0f, 0), 0);
		fixtureDef.isSensor = true;
		b2Fixture* rightSensorFixture = characterBody->CreateFixture(&fixtureDef);
		rightSensorFixture->SetUserData( new CharacterRightSensor( rightSideTouchWall) );

		soundReload.setBuffer( *ResourceHandler::instance().getSound("resources/sound/pistol_reload1.ogg") );
		soundFire.setBuffer( *ResourceHandler::instance().getSound("resources/sound/pistol_fire1.ogg") );

		soundReload.setVolume(ConfigHandler::instance().getFloat("s2_fxvolume"));
		soundFire.setVolume(ConfigHandler::instance().getFloat("s2_fxvolume"));

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
			characterBody->ApplyLinearImpulse( b2Vec2(0, 350), characterBody->GetPosition());
			setGrounded(false);
		}
		else if ( leftSideTouchWall && isWallSliding() )
		{
			characterBody->ApplyLinearImpulse( b2Vec2( -300, 350), characterBody->GetPosition());
			leftSideTouchWall = false;
			flipping = true;
		}
		else if ( rightSideTouchWall && isWallSliding() )
		{
			characterBody->ApplyLinearImpulse( b2Vec2( 300, 350), characterBody->GetPosition());
			rightSideTouchWall = false;
			flipping = true;
		}
		else
		{
			flipping = true;
		}
	}

	void Character::moveLeft() {
		moveX(true);
	}

	void Character::moveRight() {
		moveX(false);
	}

	void Character::moveUp() {
		moveY(true);
	}

	void Character::moveDown() {
		moveY(false);
	}

	void Character::moveX(bool left) {
		int maxForce, forceIteration;

		// TODO: shouldn't be hardcoded.
		if (isGrounded()) {
			maxForce = 40;
			forceIteration = 50;
		} else {
			maxForce = 18;
			forceIteration = 5;
		}
		
		if (left) { // Are we moving left?
			if(characterBody->GetLinearVelocity().x < maxForce) {
				characterBody->ApplyLinearImpulse( b2Vec2(float(forceIteration), 0), characterBody->GetPosition() );
			}
		} else { // Nope. We're moving right (the negative direction).
			if(characterBody->GetLinearVelocity().x > (-maxForce)) {
				characterBody->ApplyLinearImpulse( b2Vec2(float(-forceIteration), 0), characterBody->GetPosition() );
			}
		}
	}

	void Character::moveY(bool up) {
		// TODO: shouldn't be hardcoded.
		int maxForce = 10;
		int forceIteration = 5;
		
		if (up) { // Are we moving up?
			if(characterBody->GetLinearVelocity().y < maxForce) {
				characterBody->ApplyLinearImpulse( b2Vec2(0, forceIteration), characterBody->GetPosition() );
			}
		} else { // Nope. We're moving down (the negative direction).
			if(characterBody->GetLinearVelocity().y > -maxForce) {
				characterBody->ApplyLinearImpulse( b2Vec2(0, -forceIteration), characterBody->GetPosition() );
			}
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
		if(!isReloading())
		{
			// Fill our magazine.
			this->clip = clipSize;
			// Play the sound
			soundReload.play();
			// Force the user to wait >:)
			reloadTimer->restart();
		}
	}
	bool Character::isReloading() {
		return (reloadTimer->getElapsedTime().asMilliseconds() < reloadTime);
	}

	void Character::primaryFire(b2Vec2 &targetPos)
	{
		if (isReloading()) { return; }
		if (isShooting()) { return; }
		else { shoot(); }

		int speed = 8000;
		b2Vec2 charPos = characterBody->GetPosition();
		b2Vec2 charSpeed = characterBody->GetLinearVelocity();
		targetPos.Set(targetPos.x * 10, targetPos.y * 10); // (Don't ask. It works.)

		// We're just about to calculate these two vectors.
		b2Vec2 gunPosition; // Where the bullet should be placed.
		b2Vec2 force;		// The initial force of the bullet.

		// Direction the bullet should fly in.
		force = charPos - targetPos;
		force.Normalize();
		gunPosition = force;
		// Apply speed factor and characer's speed to our force vector.
		force.Set(-((force.x * speed) + charSpeed.x), - ((force.y * speed) + charSpeed.y));
		// Bullet spawning point should be relative to char.
		gunPosition.Set( charPos.x - gunPosition.x, gunPosition.y + charPos.y);

		// Create bullet, and add to world.
		Bullet* bullet = new Bullet(GENERIC_BULLET, 0 ,world, gunPosition, force);
		notifyObservers(BULLET_ADDED, bullet);

		// Play the sound
		//soundFire.play();
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
			this->health = 0;
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

	void Character::kill()
	{
		std::cout << "I'm a dead character. FML" << std::endl;
	}

	////////////////////////////////////////////////////////////
	// Updates char data
	////////////////////////////////////////////////////////////
	void Character::update()
	{
		if( getBody()->GetLinearVelocity().x > 0 )
			setIsFacingLeft(true);
		else if( getBody()->GetLinearVelocity().x < 0 )
			setIsFacingLeft(false);
	}

	void Character::connectToServer()
	{
		notifyObservers(CONNECT_SERVER, 0);
	}

	//Foot sensor
	Character::CharacterFootSensor::CharacterFootSensor(bool& grounded, bool& isFlipping) : grounded(grounded), isFlipping(isFlipping) {
		this->objectType = characterFootSensor;
	}
	void Character::CharacterFootSensor::onCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall) {
			grounded = true;
			isFlipping = false;
		}
	}

	void Character::CharacterFootSensor::onNoCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall)
			grounded = false;
	}

	// Leftside
	Character::CharacterLeftSensor::CharacterLeftSensor(bool& leftSideTouchWall) : leftSideTouchWall(leftSideTouchWall)	
	{
		this->objectType = characterLeftSensor;
	}

	void Character::CharacterLeftSensor::onCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall) {
			leftSideTouchWall = true;
		}
	}

	void Character::CharacterLeftSensor::onNoCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall) {
			leftSideTouchWall = false;
		}
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
		if ( crashedWith->objectType == wall) {
			rightSideTouchWall = false;
		}
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
