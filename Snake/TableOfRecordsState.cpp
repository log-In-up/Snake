#include <map>
#include <SFML/Graphics/Text.hpp>

#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "TableOfRecordsState.h"
#include "Text.h"
#include "Utils.h"

namespace Snake
{
	sf::Text* tableHeader;
	std::vector<sf::Text*> recordTableTexts;

	TableOfRecordsState::TableOfRecordsState()
	{
		tableHeader = new sf::Text();
	}

	TableOfRecordsState::~TableOfRecordsState()
	{
		delete tableHeader;

		recordTableTexts.clear();
	}

	void TableOfRecordsState::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f* origin = new sf::Vector2f(0.5f, 0.f);

		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		viewSize += sf::Vector2f(0.f, -200.f);

		DrawTextList(window, recordTableTexts, 16,
			Orientation::Vertical, Alignment::Middle,
			viewSize / 2.f, *origin);

		delete origin;
	}

	void TableOfRecordsState::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::B)
			{
				gameStateMachine->SwitchCurrentStateTo(new MainMenuState());
			}
		}
	}

	void TableOfRecordsState::Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService)
	{
		SetTextData(*tableHeader, "Table of records", resourceData.font, 16);

		recordTableTexts.push_back(tableHeader);

		std::map<std::string, unsigned int>& map = gameStateMachine->GetPointsService().GetRecordsTable();

		SelectionSort(map);

		int count = 0;
		for (auto& value : map)
		{
			if (count >= RECORD_TABLE_QUANTITY_LIMIT)
			{
				break;
			}

			sf::Text* record = new sf::Text();

			SetTextData(*record, std::to_string(count + 1) + ") " + value.first + " - " + std::to_string(value.second), resourceData.font, 16);

			recordTableTexts.push_back(record);

			++count;
		}
	}

	void TableOfRecordsState::Update(float deltaTime, sf::RenderWindow& window)
	{
	}
}