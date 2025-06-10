#include "PopUpStateMachine.h"

namespace Snake
{
	PopUpStateMachine::PopUpStateMachine(GameStateMachine& gameStateMachine) : gameStateMachine(gameStateMachine), currentPopUpState(nullptr)
	{
	}

	PopUpStateMachine::~PopUpStateMachine()
	{
	}

	void PopUpStateMachine::Draw(sf::RenderWindow& window)
	{
		currentPopUpState->Draw(window);
	}

	void PopUpStateMachine::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		currentPopUpState->HandleWindowEvents(window, event);
	}

	void PopUpStateMachine::Initialization()
	{
	}

	void PopUpStateMachine::SwitchCurrentStateTo(PopUpState* newPopUpState)
	{
		this->currentPopUpState = newPopUpState;
		this->currentPopUpState->SetPopUpStateMachineData(this, &gameStateMachine);
		this->currentPopUpState->Initialization(gameStateMachine.GetResourceData());
	}

	void PopUpStateMachine::Update(float deltaTime, sf::RenderWindow& window)
	{
		currentPopUpState->Update(deltaTime, window);
	}
}