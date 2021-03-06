	////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "StandardBullet.h"

////////////////////////////////////////////////////////////
/// Bullet
////////////////////////////////////////////////////////////

namespace mp
{
	/**
	 * Constructs a new bullet.
	 *
	 * @param owner	- Local server player id
	 * @param world	- Pointer to Box2D world
	 * @param position - Position to spawn bullet
	 * @param force	- Force to give to the bullet.
	 */
    StandardBullet::StandardBullet( sf::Int8 owner, b2World* world, b2Vec2 position, b2Vec2 force )
    {
		this->objectType = bullet;
		this->world = world;
		this->owner = owner;
		this->damage = 5;

		this->initialForce = force;
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

	void StandardBullet::onCollision(GameObject* crashedWith)
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
			this->explode();
		}
	}

	/**
	 * Destroy the bullet.
	 */
	void StandardBullet::explode() {
		//std::cout << "explode()" << std::endl;
		scheduleDeletion(BULLET_DELETED);
	}

	/**
	 * Destructor.
	 */
	StandardBullet::~StandardBullet() {
		// remove body from box2d
		world->DestroyBody(this->body);
	}
}
