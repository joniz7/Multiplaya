#include "GameState.h"

namespace mp
{
	GameState* GameState::instance = NULL;

	GameState::GameState()
	{
		//ctor
		currentState = MAIN_SCREEN;
	}

	GameState::~GameState()
	{
		//dtor
	}

	void GameState::setGameState(States state)
	{
		currentState = state;
	}

	GameState::States GameState::getGameState()
	{
		return currentState;
	}

	GameState* GameState::getInstance()
	{
		if (instance == NULL) {
			instance = new GameState();
		}
		return instance;
	}
}