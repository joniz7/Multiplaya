////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "world.h"
#include "worlddata.h"

#include <iostream>
#include <dos.h>

#include "ContactListener.h"
#include "../global.h"

////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor. Initializes the world.
	////////////////////////////////////////////////////////////
    World::World(WorldData* worldData)
    {
		this->worldData = worldData;
		// Setup the world properties
		b2Vec2 gravity(0, -9.8f);
		// Create the world
		world = new b2World(gravity);
		world->SetContactListener(new ContactListener(worldData));
    }

	////////////////////////////////////////////////////////////
	// The logic loop; updates the game world, runs Box2D etc.
	////////////////////////////////////////////////////////////
    void World::exec()
    {
		// World step properties
		const float32 timeStep = 1.0f / 60.0f;
		const int32 velocityIterations = 6;
		const int32 positionIterations = 2;

		// Define a ground body
		b2BodyDef groundBodyDef;
		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground redBox shape (also from a pool).
		// The body is also added to the world.
				
		// Define the ground box shape, extents are the half-widths of the box.
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 2.5f);

		groundBodyDef.position.Set(0.0f, -50.0f);
		b2Body* groundBody = world->CreateBody(&groundBodyDef);
		groundBody->CreateFixture(&groundBox, 0.0f);

		groundBodyDef.position.Set(0.0f, 50.0f);
		b2Body* groundBody2 = world->CreateBody(&groundBodyDef);
		groundBody2->CreateFixture(&groundBox, 0.0f);

		b2PolygonShape groundBox2;
		groundBox2.SetAsBox(2.5f, 50.0f);

		groundBodyDef.position.Set(50.0f, 0);
		b2Body* groundBody3 = world->CreateBody(&groundBodyDef);
		groundBody3->CreateFixture(&groundBox2, 0.0f);

		groundBodyDef.position.Set(-50.0f, 0);
		b2Body* groundBody4 = world->CreateBody(&groundBodyDef);
		groundBody4->CreateFixture(&groundBox2, 0.0f);

		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
		// Add two bodies to the world
		//worldData->addBody( world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f, 2.0f) );
		//worldData->addBody( world, b2Vec2(0.0f, 8.0f), b2Vec2(1.0f,2.0f) );
		worldData->addCharacter( world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f, 2.0f) );
		worldData->addCharacter( world, b2Vec2(0.0f, 8.0f), b2Vec2(1.0f, 2.0f) );
		// Create a bullet, and add it to the world.
		Bullet* b = new Bullet(BulletType::GENERIC_BULLET, 0 ,world, b2Vec2(10, 10), b2Vec2(-200, 0));
		worldData->addBullet(b);
		// Unlock world data
		worldDataMutex.unlock();
		
		// Keep track of time. Shouldn't have to do this, really. Read comment down below.
		sf::Clock clock;
		int counter = 0;
		float sum = 0;

		// Logic loop
		bool running = true;
		while(running){
			float elapsed = clock.getElapsedTime().asSeconds();
            clock.restart();

			sum += elapsed;

			//TODO: Hard coded fps limiter for Box2D as I couldn't get it to act normally. WARNING: SUPER INCORRECT AND SHOULD BE FIXED ASAP
			if(sum > 1 / 240.0f)
			{
				// Lock world data so only one thread can access world data at the same time
				worldDataMutex.lock();
				// Perform a physics step
				world->Step(timeStep, velocityIterations, positionIterations);
				// Clear physics forces in prep for next step
				world->ClearForces();
				// Save logic fps
				worldData->setLogicFps((int)(1 / sum));
				// Unlock world data
				worldDataMutex.unlock();
				sum = 0;
			}
		}
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    World::~World(){}

	////////////////////////////////////////////////////////////
	// Get world data pointer
	////////////////////////////////////////////////////////////
	WorldData* World::getWorldData()
	{
		// Lock world data
		worldDataMutex.lock();
		// Save the pointer in a temporary variable since we need to unlock the world data before returning
		WorldData* temp = worldData;
		// Unlock world data
		worldDataMutex.unlock();
		return temp;
	}
}
