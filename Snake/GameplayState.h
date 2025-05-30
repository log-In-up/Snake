#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameState.h"

namespace Snake
{
	class GameplayState : public GameState
	{
	public:
		GameplayState();
		~GameplayState();
		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	private:
		void GameplayTextMenuInitialization(ResourceData& resourceData);
		void InitializationOfTheSnake(ResourceData& resourceData, GameDifficultyService& difficultyService);
	};
}