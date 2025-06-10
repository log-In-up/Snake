#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameplayState.h"
#include "GameStateMachine.h"
#include "PopUpState.h"

namespace Snake
{
	class PopUpStateMachine
	{
	private:
		PopUpState* currentPopUpState;
		GameStateMachine& gameStateMachine;
	public:
		PopUpStateMachine(GameStateMachine& gameStateMachine);
		~PopUpStateMachine();

		void Draw(sf::RenderWindow& window);
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event);
		void Initialization();
		void SwitchCurrentStateTo(PopUpState* newPopUpState);
		void Update(float deltaTime, sf::RenderWindow& window);
	};
}