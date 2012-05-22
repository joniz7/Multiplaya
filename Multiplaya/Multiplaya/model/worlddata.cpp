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

		isClient = false;
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
				bullet->addObserver(this);
				bullets.push_back(bullet);
				notifyObservers(BULLET_ADDED, bullet);
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
		
		c->addObserver(this);
		characters.push_back(c);
		notifyObservers(CHARACTER_ADDED, c);

		return true;
    }

	bool WorldData::addCharacter(b2World* world, b2Vec2 pos, b2Vec2 size, sf::Int8 clientID)
	{
		std::cout << "Adding character" << std::endl;

		Character* c = new Character(world, pos, size, clientID);
		c ->addObserver(this);
		notifyObservers(CHARACTER_ADDED, c);
		characters.push_back( c );
		std::cout << "Done adding character " << std::endl;
		return true;
	}

	void WorldData::removeCharacter(sf::Int8 ID)
	{
		for(unsigned int i = 0; i<characters.size(); i++)
		{
			Character* character = characters.at(i);
			if(character->getClientID() == ID)
			{
				notifyObservers(CHARACTER_DELETED, (void*) i);
				worldDataMutex.lock();
				characters.erase(characters.begin()+i);
				worldDataMutex.unlock();


			}
		}
	}

	bool WorldData::exists(sf::Int8 clientID)
	{
		for(unsigned int i = 0; i<characters.size(); i++)
		{
			Character* character = characters.at(i);
			if(character->getClientID() == clientID)
			{
				return true;
			}
		}

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

	void WorldData::addWall( b2World* world, float xPos, float yPos, float width, float height )
	{
		walls.push_back(new Wall(world, xPos, yPos, width, height));
	}

	void WorldData::addChain( b2World* world, b2Vec2 vertices[], int length, float friction )
	{
		chains.push_back(new WorldChain(world,vertices,length,friction));
	}

	void WorldData::clearPhysics()
	{
		for(std::vector<WorldChain*>::iterator it = chains.begin(); it != chains.end(); ++it)
			delete((*it));
		chains.clear();
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
				notifyObservers(BULLET_DELETED, (void*) i);
				worldDataMutex.lock();
				bullets.erase(bullets.begin() + i);
				worldDataMutex.unlock();
			}
		}
	}

	void WorldData::removeAllBullets()
	{
		for(unsigned int i=0; i<bullets.size(); i++)
		{
			scheduleBulletForDeletion(bullets.at(i));
			removeBullet(bullets.at(i));
		}
	}


	Character* WorldData::getCharacter(sf::Int8 clientID)
	{
		for(unsigned int i = 0; i < characters.size(); i++)
		{
			if(characters.at(i)->getClientID() == clientID)
			{
				return characters.at(i);
			}
		}
		return NULL;
	}

	void WorldData::notify(Event e, void* object)
	{
		if (e == BULLET_DELETED)
		{
			Bullet* bullet = (Bullet*) object;
			//bullet should be removed from box2d world after timestep
			scheduleBulletForDeletion(bullet);
			// remove bullet from bullets vector in worlddata and view
			removeBullet(bullet);
		}
		else if (e == BULLET_ADDED)
		{
			Bullet* bullet = (Bullet*) object;
			addBullet(bullet);
		}
		else if (e == CONNECT_SERVER)
		{
			notifyObservers(CONNECT_SERVER, 0);
		}
	}

}
