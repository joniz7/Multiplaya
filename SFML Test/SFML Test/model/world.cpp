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
		b2Vec2 gravity(0, -20.8f);
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
		
		// if inside lock, bullets doesn't show. whyy??
		worldData->addWall(world, 0.0f, -50.0f, 50.0f, 2.5f);
		worldData->addWall(world, 0.0f, 50.0f, 50.0f, 2.5f);
		worldData->addWall(world, 50.0f, 0, 2.5f, 50.0f);
		worldData->addWall(world, -50.0f, 0, 2.5f, 50.0f);

		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();
	
		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground redBox shape (also from a pool).
		// The body is also added to the world.
		// Define the ground box shape, extents are the half-widths of the box.
		// Create a bullet, and add it to the world.
		Bullet* b = new Bullet(BulletType::GENERIC_BULLET, 0 , world, b2Vec2(10, 10), b2Vec2(-200, 0), worldData);
		worldData->addBullet(b);
		Bullet* ba = new Bullet(BulletType::GENERIC_BULLET, 0 ,world, b2Vec2(20, 30), b2Vec2(-200, 0), worldData);
		worldData->addBullet(ba);
		// Add two bodies to the world
		worldData->addCharacter( world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f, 2.0f) );
		worldData->addCharacter( world, b2Vec2(0.0f, 8.0f), b2Vec2(1.0f, 2.0f) );
		worldData->createPlayer();
	
		// Unlock world data
		worldDataMutex.unlock();
		

		// Keep track of time. Shouldn't have to do this, really. Read comment down below.
		sf::Clock clock;
		int counter = 0;
		float sum = 0;

		// Logic loop
		bool running = true;
		while(running){
            clock.restart();
			// Lock world data so only one thread can access world data at the same time
			worldDataMutex.lock();
			// Perform a physics step
			world->Step(timeStep, velocityIterations, positionIterations);
			// Clear physics forces in prep for next step
			world->ClearForces();
			// Get frame time
			float elapsed = clock.getElapsedTime().asSeconds();
			// Save logic fps
			worldData->setLogicFps((int)(1 / elapsed));
			// Unlock world data
			worldDataMutex.unlock();
			sum = 0;

			if(elapsed<(1 / 60.0f))
			{

				sf::sleep( sf::seconds( (1 / 60.0f)-elapsed ) );

				// Lock world data so only one thread can access world data at the same time
				worldDataMutex.lock();
				// Perform a physics step
				world->Step(timeStep, velocityIterations, positionIterations);
				// Clear physics forces in prep for next step
				world->ClearForces();
				// Save logic fps
				worldData->setLogicFps((int)(1 / sum));
				worldData->getPlayer()->update();
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
