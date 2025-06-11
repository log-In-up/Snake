#include <SFML/Graphics/Text.hpp>

#include "AddNamePopUpState.h"
#include "PopUpStateMachine.h"
#include "RecordTablePopUpState.h"
#include "Text.h"

namespace Snake
{
	sf::Text* nameOfPlayer;
	sf::Text* enterName;
	sf::Text* enterNameHint;
	std::vector<sf::Text*>* addNameTexts;
	std::string inputString;

	AddNamePopUpState::AddNamePopUpState()
	{
		nameOfPlayer = new sf::Text();
		enterName = new sf::Text();
		enterNameHint = new sf::Text();

		addNameTexts = new std::vector<sf::Text*>();
		addNameTexts->push_back(enterName);
		addNameTexts->push_back(nameOfPlayer);
		addNameTexts->push_back(enterNameHint);
	}

	AddNamePopUpState::~AddNamePopUpState()
	{
		delete nameOfPlayer;
		delete enterName;
		delete enterNameHint;

		addNameTexts->clear();
		delete addNameTexts;
	}

	void AddNamePopUpState::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f* origin = new sf::Vector2f(0.5f, 0.f);

		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		viewSize += sf::Vector2f(0.f, -200.f);

		DrawTextList(window, *addNameTexts, 16,
			Orientation::Vertical, Alignment::Middle,
			viewSize / 2.f, *origin);

		delete origin;
	}

	void AddNamePopUpState::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter && !inputString.empty())
			{
				gameStateMachine->GetPointsService().AddRecord(inputString, gameStateMachine->GetPointsService().GetPoints());
				popUpStateMachine->SwitchCurrentStateTo(new RecordTablePopUpState(*gameStateMachine));
			}
		}

		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < ASCII_SIZE)
			{
				if (event.text.unicode == BACKSPACE_CODE) // Backspace
				{
					if (!inputString.empty())
					{
						inputString.erase(inputString.size() - 1);
					}
				}
				else
				{
					inputString += static_cast<char>(event.text.unicode);
				}
			}
		}

		nameOfPlayer->setString(inputString);
	}

	void AddNamePopUpState::Initialization(ResourceData& resourceData)
	{
		inputString = DEFAULT_PLAYER_NAME;

		SetTextData(*enterName, "Enter name", resourceData.font, 24);
		SetTextData(*nameOfPlayer, inputString, resourceData.font, 24);
		SetTextData(*enterNameHint, "Press \"Enter \" for confirm.", resourceData.font, 24);
	}

	void AddNamePopUpState::Update(float deltaTime, sf::RenderWindow& window)
	{
	}
}