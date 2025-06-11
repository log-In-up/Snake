#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "GameState.h"
#include "TextMenu.h"

namespace Snake
{
	class MainMenuState : public GameState
	{
	public:
		MainMenuState(GameStateMachine& gameStateMachine);
		~MainMenuState();
		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	private:
		std::vector<MenuItem> GetAListOfDifficulties(ResourceData& resourceData, GameDifficultyService& difficultyService);
	};
}