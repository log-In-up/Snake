#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameplayState.h"
#include "PopUpState.h"
#include "ResourceLoader.h"

namespace Snake
{
	class EnterNamePopUpState : public PopUpState
	{
	public:
		EnterNamePopUpState();
		~EnterNamePopUpState();

		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	};
}