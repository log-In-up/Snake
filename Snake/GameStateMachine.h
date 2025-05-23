#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameState.h"
#include "ResourceLoader.h"

namespace Snake
{
	class GameStateMachine
	{
	private:
		ResourceData& resourceData;
		GameState* currentGameState;
	public:
		GameStateMachine(GameState* gameStartingState, ResourceData& resourceData) : resourceData(resourceData), currentGameState(nullptr)
		{
			this->SwitchCurrentStateTo(gameStartingState);
		}

		~GameStateMachine()
		{
			delete currentGameState;
		}

		void Draw(sf::RenderWindow& window);
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event);
		void Initialization();
		void SwitchCurrentStateTo(GameState* newGameState);
		void Update(float deltaTime, sf::RenderWindow& window);
	};
}