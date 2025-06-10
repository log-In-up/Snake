#include <SFML/System/Vector2.hpp>

#include "AddNamePopUpState.h"
#include "EnterNamePopUpState.h"
#include "PopUpStateMachine.h"
#include "RecordTablePopUpState.h"
#include "Text.h"
#include "TextMenu.h"

namespace Snake
{
	TextMenu* enterNameTextMenu;

	EnterNamePopUpState::EnterNamePopUpState()
	{
		enterNameTextMenu = new TextMenu();
	}

	EnterNamePopUpState::~EnterNamePopUpState()
	{
		delete enterNameTextMenu;
	}

	void EnterNamePopUpState::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f* origin = new sf::Vector2f(0.5f, 0.f);

		enterNameTextMenu->Draw(window, *origin, 150.f);

		delete origin;
	}

	void EnterNamePopUpState::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		enterNameTextMenu->HandleWindowEvents(window, event);
	}

	void EnterNamePopUpState::Initialization(ResourceData& resourceData)
	{
		MenuItem no;
		SetTextData(no.text, "No", resourceData.font, 24);
		no.onPressCallback = [this](MenuItem& item)
			{
				popUpStateMachine->SwitchCurrentStateTo(new RecordTablePopUpState());
			};

		MenuItem yes;
		SetTextData(yes.text, "Yes", resourceData.font, 24);
		yes.onPressCallback = [this](MenuItem& item)
			{
				popUpStateMachine->SwitchCurrentStateTo(new AddNamePopUpState());
			};

		MenuItem mainMenu;
		SetTextData(mainMenu.hintText, "Enter name", resourceData.font, 48, sf::Color::White);
		SetChildrenData(mainMenu, Orientation::Vertical, Alignment::Middle, 10.f);
		mainMenu.childrens.push_back(no);
		mainMenu.childrens.push_back(yes);

		enterNameTextMenu->Initialization(mainMenu);
	}

	void EnterNamePopUpState::Update(float deltaTime, sf::RenderWindow& window)
	{
	}
}