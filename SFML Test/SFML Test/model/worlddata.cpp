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
    WorldData::WorldData() 
	{
		logicFps = 0;
		// TODO hardcoded. not good !1!
		currentCharacterId = 0;
	}

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
			case GENERIC_BULLET:
				bullets.push_back(bullet);
				notify(BULLET_ADDED, bullet);
				//std::cout<< "Added a bullet. Total count: " << bullets.size() <<std::endl;
				return true;

				break;
		}
		return false;
    }

	////////////////////////////////////////////////////////////
	// Adds a character to the world
	// returns true upon success
	////////////////////////////////////////////////////////////
    bool WorldData::addCharacter(Character* c)
    {
		std::cout << "Adding character" << std::endl;

		characters.push_back(c);
		return true;
    }

	bool WorldData::addCharacter(b2World* world, b2Vec2 pos, b2Vec2 size, sf::Int8 clientID)
	{

		characters.push_back( new Character(this, world, pos, size, clientID) );

		return true;
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
		b2Body* body = world->CreateBody(&bodyDef);

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
		fixtureDef.isSensor = false;

		body->CreateFixture(&fixtureDef);
		body->SetFixedRotation(true);
		addBody(body);

		return true;
    }

	void WorldData::addWall( b2World* world, float xPos, float yPos, float width, float height)
	{
		walls.push_back(new Wall(world, xPos, yPos, width, height));
	}

	bool WorldData::addBody( b2Body* body  )
    {
		bodies.push_back( body );
		return true;
    }

	//Schedule bullet object for deletion our next logic iteration.
	void WorldData::scheduleBulletForDeletion(Bullet* bullet) {
		bulletsToRemove.push_back(bullet);
	}

	void WorldData::removeBullet(Bullet* bullet)
	{
		if (bullets.size() > 0) {
			std::vector<Bullet*>::iterator it = find(bullets.begin(), bullets.end(), bullet);
			if ( it != bullets.end())
			{
				int i = (it - bullets.begin());
				notify(BULLET_DELETED, (void*) i);
				bullets.erase(bullets.begin() + i);
			}
		}
	}

	Character* WorldData::getCharacter(sf::Int8 clientID)
	{
		for(int i = 0; i < characters.size(); i++)
		{
			if(characters.at(i)->getClientID() == clientID)
			{
				return characters.at(i);
			}
		}
	}

}
