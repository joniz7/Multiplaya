////////////////////////////////////////////////////////////
/// Player class.  Checks user input and such.
////////////////////////////////////////////////////////////
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "../sfml.h"
#include "../global.h"
#include "../model/character.h"
#include "../services/input.h"


namespace mp
{
	class Player
	{
		public:
			Player();
			~Player();


			void update(const sf::Vector2f &mousePos);

			/// Set the player's current character
			void setCharacter(Character* character);
			/// Returns the player's current character
			Character* getCharacter() { return character; }
		private:
			Character* character;
			bool released;
			WorldData* worldData;
			b2World* world;

			Input* input;

			void checkUserInput(const sf::Vector2f &mousePos);

			bool pressingKeyForMovingUp();
			bool pressingKeyForMovingDown();
			bool pressingKeyForPrimaryFire();
			bool pressingKeyForJumping();
			bool pressingKeyForConnecting();

			void moveLeft(int maxForce, int forceIteration);
			void moveRight(int maxForce, int forceIteration);
			void moveUp();
			void moveDown();

	};
}

#endif
