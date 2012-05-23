// Class header
#include "DefaultCharacter.h"

namespace mp
{
	/**
	 * Creates a new DefaultCharacter.
	 * 
	 * @param world - the physics world the character should belong to.
	 * @param pos - the position of the character in the world.
	 * @param size - the size of the character, physics-wise.
	 * @param clientID - which of the players this character belongs to.
	 */
    DefaultCharacter::DefaultCharacter(b2World* world, b2Vec2 pos, b2Vec2 size, sf::Int8 clientID)
    {
		this->world = world;
		this->bodySize = size;

		this->objectType = character;
		this->grounded = false;
		this->leftSideTouchWall = false;
		this->rightSideTouchWall = false;
		this->walking = false;
		this->dead = false;
		this->maxHealth = 80;
		this->setHealth(50); // TODO should default value be defined elsewhere?
		this->cooldown = 100; // milliseconds in between shots.
		this->reloadTime = 1000; // Milliseconds it takes to reload.
		this->clipSize = 11; // Amount of bullets magazine holds.
		this->clip = clipSize; // Begin game fully loaded.
		this->wallSliding = false;
		this->floorSliding = false;
		this->flipping = false;
		this->facingLeft = true;
		this->focusing = false;
		this->backwards = false;
		this->shouldFaceLeft = true;
		this->linearDamping = 10;

		this->kills  = 0;// Kill stat.
		this->deaths = 0;// Death stat.

		this->clientID = clientID;

		this->shootingTimer = new sf::Clock();
		this->reloadTimer = new sf::Clock();

		createBody(pos);

		soundReload.setBuffer( *ResourceHandler::instance().getSound("resources/sound/pistol_reload1.ogg") );
		soundFire.setBuffer( *ResourceHandler::instance().getSound("resources/sound/pistol_fire1.ogg") );
		soundJump.setBuffer( *ResourceHandler::instance().getSound("resources/sound/char_jump.ogg") );

		soundReload.setVolume(ConfigHandler::instance().getFloat("s2_fxvolume"));
		soundFire.setVolume(ConfigHandler::instance().getFloat("s2_fxvolume"));
		soundJump.setVolume(ConfigHandler::instance().getFloat("s2_fxvolume"));

    }

	/**
	 * Sets the client ID for the character.
	 * Also creates a new body with the new client ID
	 */
	void DefaultCharacter::setClientID(sf::Int8 ID) {
		this->clientID = ID;
		createBody(body->GetPosition());
	}

	/**
	 * Called when character collides with something.
	 */
	void DefaultCharacter::onCollision(GameObject* crashedWith)
	{
		// If we collided with bullet, take damage.
		if (crashedWith->objectType == bullet) {
			std::cout << "Collision: DefaultCharacter <-> bullet" << std::endl;
			IBullet* b = static_cast<IBullet*>( crashedWith );
			inflictDamage(b);
		}
		// No other checks neccessary?
	}

	void DefaultCharacter::createBody(b2Vec2 position) {

		// Duplicated code, should probably use code in addBody or something..
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		bodyDef.position.Set(position.x, position.y);
		body = world->CreateBody(&bodyDef);
		// Define a box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(bodySize.x, bodySize.y);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		// Override the default friction.
		fixtureDef.friction = 0.1f;
		// Set restitution
		fixtureDef.restitution = 0.0f;

		// Calculate unique identifying bits for this player.
		// (This makes us not collide with our own bullets)
		const short playerBits = short(pow(2.0, clientID + 1));
		fixtureDef.filter.categoryBits = playerBits;
		fixtureDef.filter.maskBits = 0xFFFF & (~playerBits);

		// Add the shape to the body.
		b2Fixture* characterBodyFixture = body->CreateFixture(&fixtureDef);
		characterBodyFixture->SetUserData( this );
		body->SetFixedRotation(true);

		b2CircleShape circleShape;

		circleShape.m_radius = bodySize.x*0.75f;
		circleShape.m_p.Set(0, -bodySize.y);

		fixtureDef.shape = &circleShape;

		//add foot sensor fixture
		dynamicBox.SetAsBox(bodySize.x*0.5f, 0.3f, b2Vec2(0,-1.7f), 0);
		fixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = body->CreateFixture(&fixtureDef);
		footSensorFixture->SetUserData( new CharacterFootSensor( grounded, flipping ) );

		fixtureDef.shape = &dynamicBox;

		//add left sensor fixture
		dynamicBox.SetAsBox(0.1f, 1, b2Vec2(1.1f, 0), 0);
		fixtureDef.isSensor = true;
		b2Fixture* leftSensorFixture = body->CreateFixture(&fixtureDef);
		leftSensorFixture->SetUserData( new CharacterLeftSensor( leftSideTouchWall ) );

		//add right sensor fixture
		dynamicBox.SetAsBox(0.1f, 1, b2Vec2(-1.1f, 0), 0);
		fixtureDef.isSensor = true;
		b2Fixture* rightSensorFixture = body->CreateFixture(&fixtureDef);
		rightSensorFixture->SetUserData( new CharacterRightSensor( rightSideTouchWall) );

	}

	/**
	 * Makes the character jump.
	 * Handles wall-jumping as well as regular jumping.
	 */
	void DefaultCharacter::jump()
	{
		if ( grounded ) {
			body->ApplyLinearImpulse( b2Vec2(0, 450), body->GetPosition());
			setGrounded(false);
			setWalking(false);
		}
		else if ( leftSideTouchWall  )
		{
			soundJump.play();
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x,0));
			if(wallSliding)
				body->ApplyLinearImpulse( b2Vec2( -300, 550), body->GetPosition());
			else
				body->ApplyLinearImpulse( b2Vec2( -300, 300), body->GetPosition());
			leftSideTouchWall = false;
			flipping = true;
		}
		else if ( rightSideTouchWall  )
		{
			soundJump.play();
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x,0));
			if(wallSliding)
				body->ApplyLinearImpulse( b2Vec2( 300, 550), body->GetPosition());
			else
				body->ApplyLinearImpulse( b2Vec2( 300, 300), body->GetPosition());
			rightSideTouchWall = false;
			flipping = true;
		}
		else
		{
			flipping = true;
		}
	}

	/**
	 * Move the character to the left.
	 */
	void DefaultCharacter::moveLeft() {
		moveX(true);
	}

	/**
	 * Move the character to the right.
	 */
	void DefaultCharacter::moveRight() {
		moveX(false);
	}

	/**
	 * Move the character upwards.
	 */
	void DefaultCharacter::moveUp() {
		moveY(true);
	}

	/**
	 * Move the character downwards.
	 */
	void DefaultCharacter::moveDown() {
		moveY(false);
	}

	/**
	 * Moves the character along the X axis.
	 * @param left - are we going left or right?
	 */
	void DefaultCharacter::moveX(bool left) {
		int maxForce, forceIteration;

		// TODO: shouldn't be hardcoded.
		if (isGrounded()) {
			if(isFocusing())
				maxForce = 15;
			else
				maxForce = 40;
			forceIteration = 25;
		} else {
			if(isFocusing())
				maxForce = 15;
			else
				maxForce = 40;
			forceIteration = 20;
		}
		
		if (left) { // Are we moving left?
			if(body->GetLinearVelocity().x < maxForce) {
				body->ApplyLinearImpulse( b2Vec2(float(forceIteration), 0), body->GetPosition() );
			}
		} else { // Nope. We're moving right (the negative direction).
			if(body->GetLinearVelocity().x > (-maxForce)) {
				body->ApplyLinearImpulse( b2Vec2(float(-forceIteration), 0), body->GetPosition() );
			}
		}
	}

	/**
	 * Moves the character along the Y axis.
	 * @param up - are we going up or down?
	 */
	void DefaultCharacter::moveY(bool up) {
		// TODO: shouldn't be hardcoded.
		int maxForce = 10;
		int forceIteration = 5;
		
		if (up) { // Are we moving up?
			if(body->GetLinearVelocity().y < maxForce) {
				body->ApplyLinearImpulse( b2Vec2(0, (float)forceIteration), body->GetPosition() );
			}
		} else { // Nope. We're moving down (the negative direction).
			if(body->GetLinearVelocity().y > -maxForce) {
				body->ApplyLinearImpulse( b2Vec2(0, -(float)forceIteration), body->GetPosition() );
			}
		}
	}

	/**
	 * Decreases bullets in clip, reloads if neccessary.
	 * Note: Private method, call primaryFire() if you want to initiate shooting!
	 */
	void DefaultCharacter::shoot() {
		if (--clip <= 0) {
			this->reload();
		}
		else {
			shootingTimer->restart();
		}
	}

	/// Checks if the character is shooting
	bool DefaultCharacter::isShooting() {
		return (shootingTimer->getElapsedTime().asMilliseconds() < cooldown);
	}

	/**
	 * Reloads the character's weapon. Replenishes the character's clip fully.
	 */
	void DefaultCharacter::reload() {
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

	/// Checks if the character is reloading.
	bool DefaultCharacter::isReloading() {
		return (reloadTimer->getElapsedTime().asMilliseconds() < reloadTime);
	}

	/**
	 * Fires a bullet towards the specified position.
	 * Calculates which force to give the bullet using targetPos and character's position.
	 *
	 * @param targetPos - where the bullet should fly towards.
	 */
	void DefaultCharacter::primaryFire(b2Vec2 &targetPos)
	{
		if (isReloading()) { return; }
		else if (isShooting()) { return; }
		else if (!isFocusing()) { return; }
		else { shoot(); }

		int speed = 8000;
		b2Vec2 charPos = body->GetPosition();
		b2Vec2 charSpeed = body->GetLinearVelocity();
		targetPos.Set(targetPos.x / PIXEL_SCALE, targetPos.y / PIXEL_SCALE); // (Don't ask. It works.)

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
		IBullet* bullet = new StandardBullet( clientID , world, gunPosition, force);
		notifyObservers(BULLET_ADDED, bullet);

		// Play the sound
		soundFire.play();
	}

	/**
	 * Inflicts damage, based on the supplied bullet.
	 * @param b - this was the bullet that hit us.
	 */
	void DefaultCharacter::inflictDamage(IBullet* b) {
		// Should different kinds of bullets inflict different damage?
		short damage = 10;

		short hp = this->getHealth();
		hp -= damage;
		this->setHealth(hp);
	}

	/**
	 * Changes the character's health.
	 * If health<1, kills the character.
	 */
	void DefaultCharacter::setHealth(short health) {
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

	/**
	 * Returns the character's health level.
	 * @returns a number between 0 and 8.
	 */
	short DefaultCharacter::getHealthState() {
		int result = (health/10);
		if ((result == 0) && health>0) {
			result = 1;
		}
		return result;
	}

	/// Kills the character
	void DefaultCharacter::kill()
	{
		std::cout << "I'm a dead character. FML" << std::endl;
		notifyObservers(CHARACTER_DIED, this);
		dead = true;
	}

	/// Updates the character data.	
	void DefaultCharacter::update()
	{
		// Get contact list (contact edges)
		b2ContactEdge* ce = getBody()->GetContactList();
		// Reset states
		grounded = false;
		leftSideTouchWall = false;
		rightSideTouchWall = false;
		// Loop through contact edges
		while(ce != NULL)
		{
			// Check sensors
			if (ce->contact->IsTouching())
			{
				if( ((CharacterFootSensor*)(ce->contact->GetFixtureB()->GetUserData()))->objectType == characterFootSensor )
					grounded = true;
				if( ((CharacterLeftSensor*)(ce->contact->GetFixtureB()->GetUserData()))->objectType == characterLeftSensor && ((CharacterLeftSensor*)(ce->contact->GetFixtureA()->GetUserData()))->objectType != character )
					leftSideTouchWall = true;
				if( ((CharacterRightSensor*)(ce->contact->GetFixtureB()->GetUserData()))->objectType == characterRightSensor && ((CharacterRightSensor*)(ce->contact->GetFixtureA()->GetUserData()))->objectType != character )
					rightSideTouchWall = true;
			}
			// Get next contact edge
			ce = ce->next;
		}

		// Determine based on character speed what direction we should be facing...
		if( getBody()->GetLinearVelocity().x > 0 )
			shouldFaceLeft = true;
		else if( getBody()->GetLinearVelocity().x < 0 )
			shouldFaceLeft = false;

		// ...although focusing overrides that by facing the way we're aiming
		if( isFocusing() && !isWallSliding() )
		{
			b2Vec2 charPos = body->GetPosition();
			if(charPos.x<targetPos.x)
				setIsFacingLeft(true);
			else
				setIsFacingLeft(false);
		}
		else
		{
			if( shouldFaceLeft )
				setIsFacingLeft(true);
			else
				setIsFacingLeft(false);
		}

		// Determine backwards status (for animation purposes)
		if(facingLeft != shouldFaceLeft)
			backwards = true;
		else
			backwards = false;

		// Handle linear damping based on what we are doing. When we are moving on the ground or falling through the air, linear damping should be nil.
		if( isWallSliding() )
			getBody()->SetLinearDamping(linearDamping);
		else if( !isGrounded() )
			getBody()->SetLinearDamping(0);
		else if( isWalking() )
		{
			if(isWalking())
			{
				if( isFocusing() && abs(getBody()->GetLinearVelocity().x)>15 )
					getBody()->SetLinearDamping(linearDamping);
				else
					getBody()->SetLinearDamping(0);
			}
			else
				getBody()->SetLinearDamping(0);
		}
		else if( !isGrounded() )
			getBody()->SetLinearDamping(0);
		else
			getBody()->SetLinearDamping(linearDamping);
	}

	/// Destructor.	
    DefaultCharacter::~DefaultCharacter()
    {
		delete shootingTimer;
		delete reloadTimer;

    }

	/// Create a new foot sensor.
	DefaultCharacter::CharacterFootSensor::CharacterFootSensor(bool& grounded, bool& isFlipping) : grounded(grounded), isFlipping(isFlipping) {
		this->objectType = characterFootSensor;
	}
	/// Reacts when we start colliding with something.
	void DefaultCharacter::CharacterFootSensor::onCollision(GameObject* crashedWith) {

	}
	/// Reacts when we stop colliding with something.
	void DefaultCharacter::CharacterFootSensor::onNoCollision(GameObject* crashedWith) {

	}

	/**
	 * Create a new left sensor.
	 */
	DefaultCharacter::CharacterLeftSensor::CharacterLeftSensor(bool& leftSideTouchWall) : leftSideTouchWall(leftSideTouchWall)	
	{
		this->objectType = characterLeftSensor;
	}
	/// Reacts when we start colliding with something.
	void DefaultCharacter::CharacterLeftSensor::onCollision(GameObject* crashedWith) {

	}
	/// Reacts when we stop colliding with something.
	void DefaultCharacter::CharacterLeftSensor::onNoCollision(GameObject* crashedWith) {

	}

	/// Create a new left sensor.
	DefaultCharacter::CharacterRightSensor::CharacterRightSensor(bool& rightSideTouchWall) : rightSideTouchWall(rightSideTouchWall) {
		this->objectType = characterRightSensor;
	}
	/// Reacts when we start colliding with something.
	void DefaultCharacter::CharacterRightSensor::onCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall) {
			rightSideTouchWall = true;
		}
	}
	/// Reacts when we stop colliding with something.
	void DefaultCharacter::CharacterRightSensor::onNoCollision(GameObject* crashedWith) {
		if ( crashedWith->objectType == wall) {
			rightSideTouchWall = false;
		}
	}
}
