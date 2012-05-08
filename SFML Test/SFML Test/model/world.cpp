////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "world.h"
#include "worlddata.h"

#include <iostream>

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

		// Add two test characters to the world.
		worldData->addCharacter( new Character(worldData, world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f, 2.0f)) );
		worldData->addCharacter( new Character(worldData, world, b2Vec2(0.0f, 8.0f), b2Vec2(1.0f, 2.0f)) );
		// Create player (which controls char 1).
		worldData->createPlayer(1);

		// Unlock world data
		worldDataMutex.unlock();

		// Keep track of time.
		sf::Clock clock;

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
			// Delete bullets, now that we're finished with physics.
			deleteBullets();
			// Get frame time
			float elapsed = clock.getElapsedTime().asSeconds();
			// Save logic fps
			worldData->setLogicFps((int)(1 / elapsed));
			// Get player input.
			worldData->getPlayer()->update();

			// Unlock world data
			worldDataMutex.unlock();

			// Have we finished faster than expected?
			if(elapsed<(1 / 60.0f))
			{	// Leave the arena now and rest - you've earned it.
				sf::sleep( sf::seconds( (1 / 60.0f)-elapsed ) );
			}
		}
    }

	void World::deleteBullets()
	{
		std::vector<Bullet*>* bulletsToRemove = worldData->getBulletsToRemove();
		// Check if we have bullets to remove.
		if (bulletsToRemove->size() > 0) {
			std::vector<Bullet*>::iterator it;
			for ( it = bulletsToRemove->begin() ; it < bulletsToRemove->end(); it++ ) {
				Bullet* bullet = (*it);
 				delete bullet;
			}
			bulletsToRemove->clear();
		}
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    World::~World(){}

}
