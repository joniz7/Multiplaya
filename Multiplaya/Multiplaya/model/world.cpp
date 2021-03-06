////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "world.h"
#include "worlddata.h"

#include <iostream>
#include <fstream>

#include "../services/ContactListener.h"
#include "../includes/Global.h"



namespace mp
{
	/**
	 * Creates a new World, based on the supplied worldData.
	 * 
	 * @param worldData - the data container to use for the world.
	 */
    World::World(WorldData* worldData) {
		this->worldData = worldData;
		reset();
    }

	/**
	 * Creates a fresh instance of the physics world.
	 */
	void World::reset() {
		worldData->reset();

		// Setup the world properties
		const b2Vec2 gravity(0, -9.8f * 8);
		// Create the world
		world = new b2World(gravity);

		worldDataMutex.lock();
		world->SetContactListener(new ContactListener());
		worldDataMutex.unlock();

		// World step properties
		timeStep = 1.0f / 60.0f;
		velocityIterations = 6;
		positionIterations = 3;
		clock = new sf::Clock();

		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();

		// Add test character to the world.
		worldData->addCharacter( world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f, 2.0f), 0 );
		//worldData->addCharacter( world, b2Vec2(2.0f, 4.0f), b2Vec2(1.0f, 2.0f), 1 );

		// Unlock world data
		worldDataMutex.unlock();

		// Load world physics
		loadMap("resources/maps/test");
	}

	/**
	 * The logic loop; updates the game world, runs Box2D and everything else.
	 */
    void World::exec() {
			clock->restart();
			// Perform a physics step
			world->Step(timeStep, velocityIterations, positionIterations);

			// Clear physics forces in prep for next step
			world->ClearForces();

			// Nullify bullet gravity		-9.8f * 8
			std::vector<IBullet*> bulletVec = *worldData->getBullets();

			for(std::vector<IBullet*>::iterator it = bulletVec.begin(); it != bulletVec.end(); ++it) {
				(*it)->getBody()->ApplyForce( b2Vec2( 0, 0.1f), (*it)->getBody()->GetPosition());
			}

			std::vector<ICharacter*> characters = *worldData->getCharacters();

			for(std::vector<ICharacter*>::iterator it = characters.begin(); it != characters.end(); ++it) {
				(*it)->update();
			}

			// Delete bullets, now that we're finished with physics.
			deleteBox2dObjects();
			// Get frame time
			float elapsed = clock->getElapsedTime().asSeconds();
			// Save logic fps
			worldDataMutex.lock();
			worldData->setLogicFps( ((int)(1 / elapsed)) / 2 );

			// Unlock world data
			worldDataMutex.unlock();

			/* // TODO: THIS IS THE PERFORMANCE HOG WE'VE BEEN LOOKING FOR FOREVER ASDFGASDEHAJSD
			// Have we finished faster than expected?
			if(elapsed<(1 / 120.0f)) {
				// Leave the arena now and rest - you've earned it.
				sf::sleep( sf::seconds( (1 / 120.0f)-elapsed ) );
			}
			*/

			if( sf::Keyboard::isKeyPressed( sf::Keyboard::F5 ) )
				reloadStuff();

    }
	
	/**
	 * Changes the gravity of the world.
	 * @param gravity - the new gravity.
	 */
	void World::setGravity(const b2Vec2 gravity) {
		this->world->SetGravity(gravity);
	}

	/**
	 * Delete box2D objects which are scheduled for deletion.
	 */
	void World::deleteBox2dObjects()
	{
		worldDataMutex.lock();
		std::vector<DynamicGameObject*>* box2dDeletionList = worldData->getDeletionList();
		// Check if we have box2d objects to remove.
		if (box2dDeletionList->size() > 0) {
			std::vector<DynamicGameObject*>::iterator it;
			for ( it = box2dDeletionList->begin() ; it != box2dDeletionList->end(); ) {
				delete *it;
				it = box2dDeletionList->erase(it);
			}
			box2dDeletionList->clear();
		}
		worldDataMutex.unlock();
	}

	/**
	 * A factory for creating a character. 
	 *
	 * @param position - where the character should be placed.
	 * @param size - the size of the character.
	 * @param clientID - which client the character should belong to.
	 */
	void World::createCharacter(b2Vec2 position, b2Vec2 size, sf::Int8 clientID)
	{
		worldDataMutex.lock();
		worldData->addCharacter( world, position, size, clientID );
		worldDataMutex.unlock();
	}

	/**
	 * A factory for creating a bullet. 
	 *
	 * @param position - where the bullet should be placed.
	 * @param force - the initial force of the bullet.
	 * @param clientID - which client the bullet should belong to.
	 */
	void World::createBullet(b2Vec2 position, b2Vec2 force, sf::Int8 clientID)
	{
		worldDataMutex.lock();
		worldData->addBullet(new StandardBullet(clientID, world, position, force));
		worldDataMutex.unlock();
	}

	/** 
	 * Load a map file.
	 */
	void World::loadMap(const std::string& path)
	{
		currentMap = path;
		std::cout<<"Loading world physics..."<<std::endl;
		loadPhysics(currentMap);
		std::cout<<"World physics loaded"<<std::endl;
		//loadGraphics(currentMap);
	}

	/** 
	 * Reload the current map.
	 */
	void World::reloadStuff()
	{
		if( ConfigHandler::instance().getBool("s_refreshphysics") )
		{
			std::cout<<std::endl<<"Reloading world physics..."<<std::endl;
			loadPhysics(currentMap);
			std::cout<<"World physics reloaded"<<std::endl;
		}

		if( ConfigHandler::instance().getBool("s_refreshtextures") )
		{
			std::cout<<std::endl<<"Reloading graphics..."<<std::endl;
			ResourceHandler::instance().reloadAllTextures();
			std::cout<<"Graphics reloaded"<<std::endl;
		}

		if( ConfigHandler::instance().getBool("s_refreshsounds") )
		{
			std::cout<<std::endl<<"Reloading sounds..."<<std::endl;
			ResourceHandler::instance().reloadAllSounds();
			std::cout<<"Sounds reloaded"<<std::endl;
		}

		std::cout<<std::endl;
	}

	/** 
	 * Load the map physics.
	 * Is called from loadMap()!
	 */
	void World::loadPhysics(const std::string& path)
	{
		// Clear any physics already loaded
		worldDataMutex.lock();
		worldData->clearPhysics();
		worldDataMutex.unlock();

		std::string physicsFile = path;
		physicsFile.append("/physics.po");

		std::ifstream fileReader;
		fileReader.open(physicsFile.c_str());
        if(!fileReader)
        {
            std::cout<<"FATAL ERROR: Unable to open physics file for map "<<physicsFile<<std::endl;
			return;
        }
		else
		{
			std::string line;
			while(getline(fileReader,line))
            {
				if(!line.empty())
				{
					bool search = true;
					int vCount = 0;
					b2Vec2 vs[99];
					while(search)
					{
						short pos1 = line.find("(");

						if(pos1==std::string::npos)
							search = false;
						else
						{
							short pos2 = line.find(")");

							std::string data = line.substr(pos1+1,pos2-(pos1+1));

							int comPos = data.find(",");

							int x = -atoi( (data.substr(0,comPos)).c_str() );
							int y = atoi( (data.substr(comPos+1,pos2-(comPos+1))).c_str() );

							vs[vCount].Set((float)x,(float)y);

							//std::cout<<"Vertex: "<<vCount<<std::endl<<"X: "<<x<<std::endl<<"Y: "<<y<<std::endl;

							std::string temp = line.substr(pos2+1,line.size()-(pos2+1));
							line = temp;
							vCount++;
						}
					}
					if(vCount>1)
					{
						worldDataMutex.lock();
						worldData->addChain(world, vs, vCount, 0.5f);
						worldDataMutex.unlock();
					}

				}
            }
		}
		fileReader.close();
	}

	/**
	 * Destructor
	 */
    World::~World(){}

}
