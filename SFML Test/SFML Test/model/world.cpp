////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "world.h"
#include "worlddata.h"

#include <iostream>
#include <fstream>

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
		const b2Vec2 gravity(0, -9.8f * 8);
		bool doSleep = true;
		// Create the world
		world = new b2World(gravity);
		worldDataMutex.lock();
		world->SetContactListener(new ContactListener(worldData));
		worldDataMutex.unlock();

		// World step properties
		timeStep = 1.0f / 60.0f;
		velocityIterations = 6;
		positionIterations = 2;
		clock = new sf::Clock();

		// Lock world data so only one thread can access world data at the same time
		worldDataMutex.lock();

		worldData->addWall(world, 0.0f, -50.0f, 50.0f, 2.5f);
		worldData->addWall(world, 0.0f, 50.0f, 50.0f, 2.5f);
		worldData->addWall(world, 50.0f, 0, 2.5f, 50.0f);
		worldData->addWall(world, -50.0f, 0, 2.5f, 50.0f);

		
		// Add´test character to the world.
		worldData->addCharacter( world, b2Vec2(0.0f, 4.0f), b2Vec2(1.0f, 2.0f), 0 );
		//worldData->addCharacter( world, b2Vec2(2.0f, 4.0f), b2Vec2(1.0f, 2.0f), 1 );
		
		// Load world physics
		loadMap("resources/maps/test");

		// Unlock world data
		worldDataMutex.unlock();

    }

	////////////////////////////////////////////////////////////
	// The logic loop; updates the game world, runs Box2D etc.
	////////////////////////////////////////////////////////////
    void World::exec() {
		// Moved loop to app.
		//bool running=true;
		//while(running) {

			clock->restart();
			// Lock world data so only one thread can access world data at the same time
			worldDataMutex.lock();
			// Perform a physics step
			world->Step(timeStep, velocityIterations, positionIterations);

			// Clear physics forces in prep for next step
			world->ClearForces();

			// Nullify bullet gravity		-9.8f * 8
			std::vector<Bullet*> bulletVec = *worldData->getBullets();

			for(std::vector<Bullet*>::iterator it = bulletVec.begin(); it != bulletVec.end(); ++it) {
				//(*it)->getBody()->ApplyForce( b2Vec2(900000.8f * 8,0), (*it)->getBody()->GetPosition() );
				(*it)->getBody()->ApplyForce( b2Vec2( 0, 0), (*it)->getBody()->GetPosition());
			}

			// Delete bullets, now that we're finished with physics.
			deleteBullets();
			// Get frame time
			float elapsed = clock->getElapsedTime().asSeconds();
			// Save logic fps
			worldData->setLogicFps((int)(1 / elapsed));

			// Unlock world data
			worldDataMutex.unlock();

			// Have we finished faster than expected?
			if(elapsed<(1 / 120.0f))
			{	// Leave the arena now and rest - you've earned it.
				sf::sleep( sf::seconds( (1 / 120.0f)-elapsed ) );
			}

		//}
    }

	void World::deleteBullets()
	{
		worldDataMutex.lock();
		std::vector<Bullet*>* bulletsToRemove = worldData->getBulletsToRemove();
		// Check if we have bullets to remove.
		if (bulletsToRemove->size() > 0) {
			std::vector<Bullet*>::iterator it;
			for ( it = bulletsToRemove->begin() ; it != bulletsToRemove->end(); ) {
				delete *it;
				it = bulletsToRemove->erase(it);
			}
			bulletsToRemove->clear();
		}
		worldDataMutex.unlock();
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
	void World::loadMap(const std::string& path)
	{
		loadPhysics(path);
		//loadGraphics(path);
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
	void World::loadPhysics(const std::string& path)
	{
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
			std::cout<<"Loading world physics"<<std::endl;;
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

							int x = atoi( (data.substr(0,comPos)).c_str() );
							int y = atoi( (data.substr(comPos+1,pos2-(comPos+1))).c_str() );

							vs[vCount].Set((float)x,(float)y);

							//std::cout<<"Vertex: "<<vCount<<std::endl<<"X: "<<x<<std::endl<<"Y: "<<y<<std::endl;

							std::string temp = line.substr(pos2+1,line.size()-(pos2+1));
							line = temp;
							vCount++;
						}
					}

					worldDataMutex.lock();
					worldData->addChain(world, vs, vCount, 0.5f);
					worldDataMutex.unlock();

				}
            }
			std::cout<<std::endl<<"World physics loaded"<<std::endl;
		}
		fileReader.close();
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    World::~World(){}

}
