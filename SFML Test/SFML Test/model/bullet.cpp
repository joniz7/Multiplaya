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
    Bullet::Bullet( BulletType type, short owner, b2World* world, b2Vec2 position, b2Vec2 force, WorldData* worldData )
    {
		//test
		this->objectType = bullet;
		this->worldData = worldData;

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
		fixtureDef.density = 1.f;
		// Override the default friction.
		fixtureDef.friction = 0.0f;
		// Set restitution
		fixtureDef.restitution = 1.0f;
		// Add the shape to the body.
		b2Fixture* testFixture = body->CreateFixture(&fixtureDef);
		testFixture->SetUserData(this);
		// Send the bullet flying
		body->ApplyForce( force, body->GetPosition() );
    }

	void Bullet::onCollision(GameObject* crashedWith)
	{
		if (crashedWith->objectType == wall) {
			// call worldData and notify deletebullet
			// delete bullet
			// delete body in box2d
			worldData->removeBullet(this);
		}
	}

	bool Bullet::operator==(const Bullet* bullet) {
        return bullet == this; 
    }
	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    Bullet::~Bullet(){}
}
