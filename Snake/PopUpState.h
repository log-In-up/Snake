#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameplayState.h"
#include "GameStateMachine.h"
#include "ResourceLoader.h"

namespace Snake
{
	class PopUpStateMachine;

	class PopUpState
	{
	protected:
		PopUpStateMachine* popUpStateMachine;
		GameStateMachine* gameStateMachine;
	public:
		PopUpState();
		virtual ~PopUpState();

		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) = 0;
		virtual void Initialization(ResourceData& resourceData) = 0;
		virtual void Update(float deltaTime, sf::RenderWindow& window) = 0;
		void SetPopUpStateMachineData(PopUpStateMachine* popUpStateMachine, GameStateMachine* gameStateMachine);
	};
}