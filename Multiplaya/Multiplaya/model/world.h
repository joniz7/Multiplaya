////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////
#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include "../services/resourcehandler.h"
#include "../services/confighandler.h"

// SFML specific headers
#include <SFML/System.hpp>

// Box2D specific headers
#include <Box2D.h>

#include "../services/input.h"

namespace mp
{
	//Forward declaration so World can have a WorldData pointer
	class WorldData;

	/**
	 * The model of the game.
	 * Handles game physics, logic, and a whole lot more.
	 * Has factories for adding stuff to the world, and an exec() method
	 * which should be called all the time when the game is running.
	 */
    class World
    {
        public:
			World(WorldData* worldData);
			void exec();
            ~World();
			b2World* getWorld(){ return world; }
			WorldData* getWorldData() { return worldData; }
			void createCharacter(b2Vec2 positions, b2Vec2 size, sf::Int8 clientID);
			void createBullet(b2Vec2 position, b2Vec2 force, sf::Int8 clientID);
			void setGravity(const b2Vec2 gravity);

			void loadMap(const std::string& path);
			void reloadStuff();
			void loadPhysics(const std::string& path);
			void reloadPhysics();
        private:
			WorldData* worldData;
			b2World* world;
			void deleteBox2dObjects();
			// World step properties
			float32 timeStep;
			int32 velocityIterations;
			int32 positionIterations;
			sf::Clock* clock;
			std::string currentMap;
    };
}

#endif
