#include "GameState.h"

namespace Snake
{
	GameState::GameState() : gameStateMachine(nullptr)
	{
	}

	GameState::~GameState()
	{
	}

	void GameState::SetGameStateMachine(GameStateMachine* gameStateMachine)
	{
		this->gameStateMachine = gameStateMachine;
	}
}