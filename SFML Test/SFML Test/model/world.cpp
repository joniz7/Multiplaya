////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "world.h"
#include "worlddata.h"

#include <iostream>
#include <dos.h>

#include "../global.h"

////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////

namespace mp
{

	void createViewThread(void* UserData)
	{
		std::cout<<"Starting view thread..."<<std::endl;
		// Cast to world data pointer
		WorldData* worldData = static_cast<WorldData*>(UserData);
		// Initialize the view and pass the world data pointer as argument
		WorldView* view = new WorldView( worldData );
		std::cout<<"View thread up and running!"<<std::endl;
		view->exec();
	}

	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    World::World()
    {
		// Setup the world properties
		b2Vec2 gravity(0,-9.8f);
		// Create the world
		world = new b2World(gravity);
		// Lock world data
		worldDataMutex.lock();
		// Initialize world data instance
		worldData = new WorldData(this);
		// Unlock world data
		worldDataMutex.unlock();
    }

	////////////////////////////////////////////////////////////
	// The logic loop; updates the game world, runs Box2D etc.
	////////////////////////////////////////////////////////////
    void World::exec()
    {
		// Launch the view thread
		sf::Thread viewThread(&createViewThread, worldData);
		viewThread.launch();
		// World step properties
		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;

		// Define a ground body
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

		// Add test stuff to the world (by adding it to world data)
		worldDataMutex.lock();
		worldData->addBody( world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f,1.0f) );
		worldData->addBody( world, b2Vec2(0.0f, 8.0f), b2Vec2(1.0f,1.0f) );
		worldData->addBullet(BulletType::GENERIC_BULLET,0,world,b2Vec2(10,10),b2Vec2(-50,0));
		// Unlock world data
		worldDataMutex.unlock();
		
		// Logic loop
		bool running = true;
		while(running){
			// Lock world data
			worldDataMutex.lock();
			// Perform a physics step
			world->Step(timeStep,velocityIterations,positionIterations);
			// Clear physics forces in prep for next step
			world->ClearForces();
			// Unlock world data
			worldDataMutex.unlock();
		}
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    World::~World()
    {

    }

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
