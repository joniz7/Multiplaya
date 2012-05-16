////////////////////////////////////////////////////////////
/// Player class.  Checks user input and such.
////////////////////////////////////////////////////////////
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

// Box2D specific headers
#include <Box2D.h>

//Defines
#include "../sfml.h"

#include "../model/character.h"


namespace mp
{
	class Player
	{
		public:
			Player();
			~Player();
			void update(const sf::Vector2f &mousePos);
			void setCharacter(Character* character);
			Character* getCharacter() { return character; }
		private:
			Character* character;
			bool released;
			WorldData* worldData;
			b2World* world;

			void checkUserInput(const sf::Vector2f &mousePos);

			bool pressingKeyForMovingRight();
			bool pressingKeyForMovingLeft();
			bool pressingKeyForMovingUp();
			bool pressingKeyForMovingDown();
			bool pressingKeyForPrimaryFire();
			bool pressingKeyForJumping();
			bool pressingKeyForConnecting();

			void moveLeft();
			void moveRight();
			void moveUp();
			void moveDown();

	};
}

#endif
