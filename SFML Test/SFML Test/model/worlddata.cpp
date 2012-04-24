////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "worlddata.h"
#include "world.h"

#include "../global.h"

////////////////////////////////////////////////////////////
/// World data class. Holds all data world class uses for 
/// easy access from view and network handler
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    WorldData::WorldData(){logicFps=0;}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    WorldData::~WorldData(){}

	////////////////////////////////////////////////////////////
	// Adds the supplied bullet to the world.
	//
	// returns true upon success.
	////////////////////////////////////////////////////////////
    bool WorldData::addBullet( Bullet* bullet )
	{
		BulletType type = bullet->getType();
		
		switch(type)
		{
			case BulletType::GENERIC_BULLET:
				bltVec.push_back(*bullet);
				std::cout<<"Added a bullet. Total count: "<< bltVec.size() <<std::endl;
				return true;
				break;
		}
		return false;
    }

	////////////////////////////////////////////////////////////
	// Adds a bullet to the world
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
    bool WorldData::addBullet( BulletType type, short owner, b2World* world, b2Vec2 position, b2Vec2 force )
    {
		std::cout<<"Added a bullet"<<std::endl;
		// Do different things depending on the type of bullet
		switch(type)
		{
			case BulletType::GENERIC_BULLET:
				bltVec.push_back( Bullet(type,owner,world,position,force) );
				return true;
				break;
		}
		return false;
    }

	////////////////////////////////////////////////////////////
	// Adds a character to the world
	// returns true upon success
	////////////////////////////////////////////////////////////
    bool WorldData::addCharacter()
    {
		return false;
    }

	////////////////////////////////////////////////////////////
	// Adds a generic body to the world
	// returns true upon success
	////////////////////////////////////////////////////////////
    bool WorldData::addBody( b2World* world, b2Vec2 position, b2Vec2 size )
    {
		std::cout<<"Added a body"<<std::endl;
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x, position.y);
		bodyVec.push_back( world->CreateBody(&bodyDef) );

		// Define a box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(size.x, size.y);
		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		// Override the default friction.
		fixtureDef.friction = 2.0f;
		// Set restitution
		fixtureDef.restitution = 0.0f;
		// Add the shape to the body.
		bodyVec.back()->CreateFixture(&fixtureDef);
		bodyVec.back()->SetFixedRotation(true);
		return true;
    }
}
