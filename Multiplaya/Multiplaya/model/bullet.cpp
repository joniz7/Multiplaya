	////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "bullet.h"

////////////////////////////////////////////////////////////
/// Bullet
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor
	//
	// type		- Type of bullet. Defined in defines.h
	// owner	- Local server player id
	// world	- Pointer to Box2D world
	// position - Position to spawn bullet
	// force	- Force to add to bullet force defined in BulletType,
	//			  usually this is the force vector of the player
	//			  who fired the bullet.
	//
	// returns true upon success
	////////////////////////////////////////////////////////////
    Bullet::Bullet( BulletType type, sf::Int8 owner, b2World* world, b2Vec2 position, b2Vec2 force )
    {
		scheduledForDeletion = false;
		this->objectType = bullet;

		this->world = world;
		// Save bullet data
		this->type = type;
		this->owner = owner;
		// Set up body definition
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x, position.y);
		// Object is literally a bullet so set the bullet flag to prevent tunneling
		bodyDef.bullet = true;
		// Add the body to the world
		body = world->CreateBody(&bodyDef);
		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		b2CircleShape circle;
		// Bullet hit box radius
		circle.m_radius = 0.25f;
		fixtureDef.shape = &circle;
		// Set the bullet density to be non-zero, so it will be dynamic.
		fixtureDef.density = 0.01f;
		// Override the default friction.
		fixtureDef.friction = 0.0f;
		// Set restitution
		fixtureDef.restitution = 1.0f;

		// Calculate unique identifying bits for this bullet.
		// (This makes us pass through our player)
		const short playerBits = short(pow(2.0, owner + 1));
		fixtureDef.filter.categoryBits = playerBits;
		fixtureDef.filter.maskBits = 0xFFFF & (~playerBits);

		// Add the shape to the body.
		b2Fixture* testFixture = body->CreateFixture(&fixtureDef);
		testFixture->SetUserData(this);
		// Send the bullet flying
		body->ApplyForce( force, body->GetPosition() );
	}

	void Bullet::onCollision(GameObject* crashedWith)
	{
		// If we collide with wall, explode.
		if (crashedWith->objectType == wall) {
			//td::cout << "Collision: bullet <-> wall" << std::endl;
			this->explode();
		}

		// If we collide with bullet... do nothing?
		else if (crashedWith->objectType == bullet) {
			//std::cout << "Collision: bullet <-> bullet" << std::endl;
		}

		// If we collide with character, explode (we handle the dmg elsewhere).
		else if (crashedWith->objectType == character) {
			std::cout << "Collision: bullet <-> character" << std::endl;
			this->explode();
		}
	}

	///////////////////////////
	// Destroy the bullet.
	///////////////////////////
	void Bullet::explode() {
		//std::cout << "explode()" << std::endl;
		if (!scheduledForDeletion)
		{
			notifyObservers(BULLET_DELETED, this);
			scheduledForDeletion = true;
		}
	}

	bool Bullet::operator==(const Bullet* bullet) {
        return bullet == this;
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    Bullet::~Bullet() {
		// Remove bullet from worldData (-> from the view).
		//worldData->removeBullet(this);
		// remove body from box2d
		world->DestroyBody(this->body);
	}
}