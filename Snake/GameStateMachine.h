#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "AudioService.h"
#include "GameDifficultyService.h"
#include "GameState.h"
#include "PointsService.h"
#include "ResourceLoader.h"

namespace Snake
{
	class GameStateMachine
	{
	private:
		AudioService* audioService;
		ResourceData& resourceData;
		GameState* currentGameState;
		GameDifficultyService* difficultyService;
		PointsService* pointsService;
	public:
		GameStateMachine(ResourceData& resourceData) : resourceData(resourceData), currentGameState(nullptr)
		{
			audioService = new AudioService(resourceData);
			difficultyService = new GameDifficultyService();
			pointsService = new PointsService();
		}

		~GameStateMachine()
		{
			delete audioService;
			delete difficultyService;
			delete pointsService;
			delete currentGameState;
		}

		PointsService& GetPointsService()
		{
			return *pointsService;
		}

		ResourceData& GetResourceData()
		{
			return resourceData;
		}

		AudioService& GetAudioService()
		{
			return *audioService;
		}

		void Draw(sf::RenderWindow& window);
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event);
		void Initialization();
		void SwitchCurrentStateTo(GameState* newGameState);
		void Update(float deltaTime, sf::RenderWindow& window);
	};
}