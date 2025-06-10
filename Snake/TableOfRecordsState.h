#pragma once
#include "GameState.h"

namespace Snake
{
	const int RECORD_TABLE_QUANTITY_LIMIT = 10;

	class TableOfRecordsState : public GameState
	{
	public:
		TableOfRecordsState();
		~TableOfRecordsState();
		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	};
}