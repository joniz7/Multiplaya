#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stddef.h>
#include "services/MusicHandler.h"

namespace mp
{
	class GameState
	{
		public:
		enum States
		{
			MAIN_SCREEN,
			JOIN_GAME,
			HOST_GAME,
			SETTINGS_SCREEN
		};

		static GameState* getInstance();

		void setGameState(States state);
		States getGameState();

		protected:

		private:
			GameState();
			virtual ~GameState();
			static GameState* instance;
			States currentState;
	};
}
#endif // GAMESTATE_H
