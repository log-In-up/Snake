#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceLoader.h"

namespace Snake
{
	class GameStateMachine;

	class GameState
	{
	protected:
		GameStateMachine* gameStateMachine;
	public:
		GameState();

		virtual ~GameState();

		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) = 0;
		virtual void Initialization(ResourceData& resourceData) = 0;
		virtual void Update(float deltaTime, sf::RenderWindow& window) = 0;
		void SetGameStateMachine(GameStateMachine* gameStateMachine);
	};
}