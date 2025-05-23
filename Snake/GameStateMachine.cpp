#include "GameStateMachine.h"

namespace Snake
{
	void GameStateMachine::Draw(sf::RenderWindow& window)
	{
		currentGameState->Draw(window);
	}

	void GameStateMachine::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		currentGameState->HandleWindowEvents(window, event);
	}

	void GameStateMachine::Initialization()
	{
	}

	void GameStateMachine::SwitchCurrentStateTo(GameState* newGameState)
	{
		this->currentGameState = newGameState;
		this->currentGameState->SetGameStateMachine(this);
		this->currentGameState->Initialization(resourceData);
	}

	void GameStateMachine::Update(float deltaTime, sf::RenderWindow& window)
	{
		currentGameState->Update(deltaTime, window);
	}
}