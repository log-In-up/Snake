#include "PopUpState.h"

namespace Snake
{
	PopUpState::PopUpState() : popUpStateMachine(nullptr), gameStateMachine(nullptr)
	{
	}

	PopUpState::~PopUpState()
	{
	}

	void PopUpState::SetPopUpStateMachineData(PopUpStateMachine* popUpStateMachine, GameStateMachine* gameStateMachine)
	{
		this->popUpStateMachine = popUpStateMachine;
		this->gameStateMachine = gameStateMachine;
	}
}