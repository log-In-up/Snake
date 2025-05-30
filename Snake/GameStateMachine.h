#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameDifficultyService.h"
#include "GameState.h"
#include "ResourceLoader.h"

namespace Snake
{
	class GameStateMachine
	{
	private:
		ResourceData& resourceData;
		GameState* currentGameState;
		GameDifficultyService* difficultyService;
	public:
		GameStateMachine(GameState* gameStartingState, ResourceData& resourceData) : resourceData(resourceData), currentGameState(nullptr)
		{
			difficultyService = new GameDifficultyService();

			this->SwitchCurrentStateTo(gameStartingState);
		}

		~GameStateMachine()
		{
			delete currentGameState;
			delete difficultyService;
		}

		void Draw(sf::RenderWindow& window);
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event);
		void Initialization();
		void SwitchCurrentStateTo(GameState* newGameState);
		void Update(float deltaTime, sf::RenderWindow& window);
	};
}