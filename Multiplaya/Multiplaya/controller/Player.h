#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

// Box2D specific headers
#include <Box2D.h>

#include "../includes/Global.h"
#include "../model/WorldData.h"
#include "../model/ICharacter.h"
#include "../services/Input.h"


namespace mp
{
	/**
	 * A class which represents the local player (handles input).
	 */
	class Player
	{
		public:
			Player();
			~Player();

			void update(const sf::Vector2f &mousePos);

			/// Set the player's current character
			void setCharacter(ICharacter* character) { this->character = character; }
			/// Returns the player's current character
			ICharacter* getCharacter() { return character; }
		private:
			ICharacter* character;
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

	};
}

#endif
