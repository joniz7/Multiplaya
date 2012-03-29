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
		// Initialize world data instance
		worldDataMutex.lock();
		worldData = new WorldData(this);
		worldDataMutex.unlock();
    }

	////////////////////////////////////////////////////////////
	// The logic loop.
	// Updates the game world, performs physic checks, repeat.
	////////////////////////////////////////////////////////////
    void World::exec()
    {

		sf::Thread viewThread(&createViewThread, worldData);
		viewThread.launch();

		worldDataMutex.lock();
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

		/*	//Old code
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
		*/

		// New code
		worldDataMutex.lock();
		worldData->addBody( world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f,1.0f) );
		worldData->addBody( world, b2Vec2(0.0f, 8.0f), b2Vec2(1.0f,1.0f) );
		worldData->addBullet(BulletType::GENERIC_BULLET,0,world,b2Vec2(10,10),b2Vec2(0,0));

		worldDataMutex.unlock();
		
		// Logic loop
		worldDataMutex.unlock();
		bool running = true;
		while(running){
			worldDataMutex.lock();
			// Perform a physics step
			world->Step(timeStep,velocityIterations,positionIterations);
			// Clear physics forces in prep for next step
			world->ClearForces();

			//std::cout<<"( "<<worldData->getBody(0)->GetPosition().x<<" , "<<worldData->getBody(0)->GetPosition().y<<" )"<<std::endl;
			
			/*
			// Get model data
			b2Vec2 position = worldData->getBody(0)->GetPosition();
			float32 angle = worldData->getBody(0)->GetAngle();
			// Get model data
			position = worldData->getBody(1)->GetPosition();
			angle = worldData->getBody(1)->GetAngle();
			b2Vec2 v = worldData->getBullet(0)->getBody()->GetLinearVelocity();
			float a = atan(v.x/v.y);
			*/
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
	// Get world
	////////////////////////////////////////////////////////////
	b2World* World::getWorld()
	{
		return world;
	}

	////////////////////////////////////////////////////////////
	// Get world data pointer
	////////////////////////////////////////////////////////////
	WorldData* World::getWorldData()
	{
		worldDataMutex.lock(); // Lock world data mutex since we are handling world data class
		std::cout<<"Someone stole the world data!"<<std::endl;
		WorldData* temp = worldData;
		worldDataMutex.unlock(); // Unlock world data mutex
		return temp;
	}
}
