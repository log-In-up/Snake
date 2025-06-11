#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "PopUpState.h"

namespace Snake
{
	const int GAMEOVER_RECORD_TABLE_QUANTITY_LIMIT = 5;

	class RecordTablePopUpState : public PopUpState
	{
	public:
		RecordTablePopUpState(GameStateMachine& gameStateMachine);
		~RecordTablePopUpState();

		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	private:
		void InitializeTheHighScoreTable(ResourceData& resourceData);
	};
}