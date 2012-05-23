// Class header
#include "worlddata.h"
#include "world.h"

#include "../includes/Global.h"

namespace mp
{

	/**
	 * Creates a new WorldData instance.
	 */
    WorldData::WorldData()
	{
		logicFps = 0;
		// TODO hardcoded. not good !1!
		currentCharacterId = 0;

		isClient = false;
	}

	/**
	 * Destructor.
	 */
    WorldData::~WorldData(){}

	/**
	 * Adds the supplied bullet to the world.
	 *
	 * @param bullet - bullet to add.
	 */
    void WorldData::addBullet( Bullet* bullet )
	{
		bullet->addObserver(this);
		bullets.push_back(bullet);
		notifyObservers(BULLET_ADDED, bullet);
    }

	/**
	 * Add the supplied character to the world.
	 * @param c - character to add.
	 */
    void WorldData::addCharacter(Character* c)
    {
		std::cout << "Adding character" << std::endl;
		
		c->addObserver(this);
		characters.push_back(c);
		notifyObservers(CHARACTER_ADDED, c);

    }

	/**
	 * Adds a character to the world.
	 */
	void WorldData::addCharacter(b2World* world, b2Vec2 pos, b2Vec2 size, sf::Int8 clientID)
	{
		std::cout << "Adding character" << std::endl;

		Character* c = new Character(world, pos, size, clientID);
		c ->addObserver(this);
		notifyObservers(CHARACTER_ADDED, c);
		characters.push_back( c );
		std::cout << "Done adding character " << std::endl;
	}

	/**
	 * Removes the character with the specified clientID from the world.
	 * @param ID - remove character belonging to this player.
	 */
	void WorldData::removeCharacter(sf::Int8 ID)
	{
		for(unsigned int i = 0; i<characters.size(); i++)
		{
			ICharacter* character = characters.at(i);
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
			ICharacter* character = characters.at(i);
			if(character->getClientID() == clientID)
			{
				return true;
			}
		}

		return false;
	}
	
	/**
	 * Adds a generic body to the world.
	 */
	 void WorldData::addBody( b2World* world, b2Vec2 position, b2Vec2 size )
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

    }

	/**
	 * Adds a new wall to the world.
	 */
	void WorldData::addWall( b2World* world, float xPos, float yPos, float width, float height )
	{
		walls.push_back(new Wall(world, xPos, yPos, width, height));
	}

	/**
	 * Adds a new chain to the world.
	 */
	void WorldData::addChain( b2World* world, b2Vec2 vertices[], int length, float friction ) {
		chains.push_back(new WorldChain(world,vertices,length,friction));
	}

	void WorldData::clearPhysics() {
		for(std::vector<WorldChain*>::iterator it = chains.begin(); it != chains.end(); ++it)
			delete((*it));
		chains.clear();
	}

	/**
	 * Adds the supplied body to the world.
	 */
	void WorldData::addBody( b2Body* body ) {
		bodies.push_back( body );
    }

	/**
	 * Schedule supplied object for deletion our next logic iteration.
	 * @param object - object to be deleted.
	 */
	void WorldData::scheduleForDeletion(DynamicGameObject* object) {
		deletionList.push_back(object);
	}

	/**
	 * Remove the supplied bullet.
	 * @param bullet - bullet to be removed.
	 */
	void WorldData::removeBullet(Bullet* bullet)
	{
		worldDataMutex.lock();
		if (bullets.size() > 0) {
			// locate bullet in vector
			std::vector<Bullet*>::iterator it = find(bullets.begin(), bullets.end(), bullet);
			if ( it != bullets.end())
			{
				// get the bullet's index
				int i = (it - bullets.begin());
				// tell the view to remove bullet from its list
				notifyObservers(BULLET_DELETED, (void*) i);
				// remove from bullet list
				bullets.erase(bullets.begin() + i);
			}
		}
		worldDataMutex.unlock();
	}

	/**
	 * Removes all bullets from the game, except the ones 
	 * belonging to the player with clientID.
	 *
	 * @param clientID - the client whose bullets should be exempt from deleting.
	 */
	void WorldData::removeAllBullets(sf::Int8 clientID)
	{
		worldDataMutex.lock();
		Bullet* bullet;
		int test1, test2;
		std::cout<<"kommer jag hit?"<<std::endl;
		for(unsigned int i = 0; i < bullets.size(); i++) {

			bullet = bullets.at(i);
			test1 = clientID, test2 = bullet->getOwner();
			std::cout<<test1<<"     "<<test2<<std::endl;
			if(bullet->getOwner() != clientID)
			{
				removeBullet(bullet);
				scheduleForDeletion(bullet);
			}
		}
		worldDataMutex.unlock();
	}

	/**
	 * Returns the character with the specified clientID.
	 */
	ICharacter* WorldData::getCharacter(sf::Int8 clientID)
	{
		for(unsigned int i = 0; i < characters.size(); i++) {
			if(characters.at(i)->getClientID() == clientID) {
				return characters.at(i);
			}
		}
		return NULL;
	}

	/**
	 * Is notified when bullets are removed, added, 
	 * or when we conenect to a server.
	 */
	void WorldData::notify(Event e, void* object)
	{
		if (e == BULLET_DELETED) {
			//worldDataMutex.lock();
			Bullet* bullet = (Bullet*) object;
			removeBullet(bullet);
			//bullet should be removed from box2d world after timestep
			//this is only done on the server
			if(!isClient)
				scheduleForDeletion(bullet);
			// remove bullet from bullets vector in worlddata and view
			//worldDataMutex.unlock();
		}
		else if (e == BULLET_ADDED) {

			Bullet* bullet = (Bullet*) object;

			if(isClient) {
				notifyObservers(SEND_BULLET, bullet);
			}
			//worldDataMutex.lock();
			addBullet(bullet);
			//worldDataMutex.unlock();
		}
		else if (e == CONNECT_SERVER) {
			notifyObservers(CONNECT_SERVER, 0);
		}
	}

}
