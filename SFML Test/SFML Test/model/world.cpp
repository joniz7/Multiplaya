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

		// World step properties
		timeStep = 1.0f / 60.0f;
		velocityIterations = 6;
		positionIterations = 2;
		clock = new sf::Clock();

		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();

		// if inside lock, bullets doesn't show. whyy??
		worldData->addWall(world, 0.0f, -50.0f, 50.0f, 2.5f);
		worldData->addWall(world, 0.0f, 50.0f, 50.0f, 2.5f);
		worldData->addWall(world, 50.0f, 0, 2.5f, 50.0f);
		worldData->addWall(world, -50.0f, 0, 2.5f, 50.0f);

		// Add´test character to the world.
		worldData->addCharacter( world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f, 2.0f), 0 );

		// Unlock world data
		worldDataMutex.unlock();

    }

	////////////////////////////////////////////////////////////
	// The logic loop; updates the game world, runs Box2D etc.
	////////////////////////////////////////////////////////////
    void World::exec() {
		while (true) 
		{
			clock->restart();
			// Lock world data so only one thread can access world data at the same time
			worldDataMutex.lock();
			// Perform a physics step
			world->Step(timeStep, velocityIterations, positionIterations);
			// Clear physics forces in prep for next step
			world->ClearForces();
			// Delete bullets, now that we're finished with physics.
			deleteBullets();
			// Get frame time
			float elapsed = clock->getElapsedTime().asSeconds();
			// Save logic fps
			worldData->setLogicFps((int)(1 / elapsed));

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

	void World::createCharacter(b2Vec2 position, b2Vec2 size, sf::Int8 clientID)
	{
		//Character* character = ;
		worldDataMutex.lock();
		worldData->addCharacter( world, position, size, clientID );
		worldDataMutex.unlock();
	}

	void World::createBullet(b2Vec2 position, b2Vec2 force, sf::Int8 clientID, BulletType type)
	{
		worldDataMutex.lock();
		worldData->addBullet(new Bullet(type, clientID, world, position, force, worldData));
		worldDataMutex.unlock();
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    World::~World(){}

}
