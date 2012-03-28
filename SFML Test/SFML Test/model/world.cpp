////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "world.h"

#include <iostream>
#include <dos.h>

////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    World::World()
    {
		std::cout << "World constructor." << std::endl;
    }

	////////////////////////////////////////////////////////////
	// The logic loop.
	// Updates the game world, performs physic checks, repeat.
	////////////////////////////////////////////////////////////
    void World::exec()
    {
		std::cout << "World exec()" << std::endl;

		// Setup the world properties
		bool doSleep = true;
		b2Vec2 gravity(0,-25.8f);
		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		// Create the world
		b2World* world;
		world = new b2World(gravity);
		world->SetAllowSleeping(doSleep);

		//Define a ground body
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -50.0f);
		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground redBox shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = world->CreateBody(&groundBodyDef);
		groundBodyDef.position.Set(0.0f, 50.0f);
		b2Body* groundBody2 = world->CreateBody(&groundBodyDef);
		groundBodyDef.position.Set(50.0f, 0);
		b2Body* groundBody3 = world->CreateBody(&groundBodyDef);
		groundBodyDef.position.Set(-50.0f, 0);
		b2Body* groundBody4 = world->CreateBody(&groundBodyDef);

		// Define the ground box shape, extents are the half-widths of the box.
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 2.5f);

		b2PolygonShape groundBox2;
		groundBox2.SetAsBox(2.5f, 50.0f);
		
		// Add the ground fixture to the ground body.
		groundBody->CreateFixture(&groundBox, 0.0f);
		groundBody2->CreateFixture(&groundBox, 0.0f);
		groundBody3->CreateFixture(&groundBox2, 0.0f);
		groundBody4->CreateFixture(&groundBox2, 0.0f);

		Bullet* boolet = new Bullet(world,b2Vec2(10,10),b2Vec2(2000,-2000));

		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 4.0f);
		b2Body* body = world->CreateBody(&bodyDef);

		b2BodyDef bodyDef2;
		bodyDef2.type = b2_dynamicBody;
		bodyDef2.position.Set(1.0f, 8.0f);
		b2Body* body2 = world->CreateBody(&bodyDef2);
		
		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);
		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		// Override the default friction.
		fixtureDef.friction = 0.9f;
		// Set restitution
		fixtureDef.restitution = 0.25f;
		// Add the shape to the body.
		body->CreateFixture(&fixtureDef);
		body2->CreateFixture(&fixtureDef);


		while(true) {



			// Perform a physics step
			world->Step(timeStep,velocityIterations,positionIterations);
			// Clear physics forces in prep for next step
			world->ClearForces();

			// Get model data
			b2Vec2 position = body->GetPosition();
			float32 angle = body->GetAngle();
			// Get model data
			position = body2->GetPosition();
			angle = body2->GetAngle();

			b2Vec2 v = boolet->getBody()->GetLinearVelocity();
			float a = atan(v.x/v.y);








		}
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    World::~World()
    {

    }
}
