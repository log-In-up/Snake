#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameState.h"

namespace Snake
{
	class CloseApplication : public GameState
	{
	public:
		CloseApplication();
		~CloseApplication();
		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	};
}