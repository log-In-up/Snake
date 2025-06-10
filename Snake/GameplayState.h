#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameState.h"

namespace Snake
{
	const float GAME_PRE_PAUSE_TIME = 2.f;

	struct GameplayData
	{
		bool isGameOver = false;
	};

	class GameplayState : public GameState
	{
	public:
		GameplayState(GameStateMachine& gameStateMachine);
		~GameplayState();
		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	private:
		bool GameIsOnPrePause(float deltaTime);
		void GameplayTextMenuInitialization(ResourceData& resourceData);
		void InitializationOfTheSnake(ResourceData& resourceData, GameDifficultyService& difficultyService);
	};
}