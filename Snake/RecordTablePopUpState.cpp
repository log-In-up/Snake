#include <map>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <vector>

#include "GameplayState.h"
#include "MainMenuState.h"
#include "PointsService.h"
#include "RecordTablePopUpState.h"
#include "Text.h"
#include "TextMenu.h"

namespace Snake
{
	TextMenu* popUpMenu;

	sf::Text* header;
	sf::Text* pointsReceivedByThePlayer;
	std::vector<sf::Text*>* popUpTableTexts;

	RecordTablePopUpState::RecordTablePopUpState()
	{
		popUpMenu = new TextMenu();
		header = new sf::Text();
		pointsReceivedByThePlayer = new sf::Text();

		popUpTableTexts = new std::vector<sf::Text*>();
	}

	RecordTablePopUpState::~RecordTablePopUpState()
	{
		delete popUpMenu;
		delete header;
		delete pointsReceivedByThePlayer;

		popUpTableTexts->clear();
		delete popUpTableTexts;
	}

	void RecordTablePopUpState::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f* origin = new sf::Vector2f(0.5f, -2.f);

		popUpMenu->Draw(window, *origin, 150.f);

		pointsReceivedByThePlayer->setString(std::to_string(gameStateMachine->GetPointsService().GetPoints()));

		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		viewSize += sf::Vector2f(0.f, -200.f);

		origin = new sf::Vector2f(0.5f, 0.f);

		DrawTextList(window, *popUpTableTexts, 16,
			Orientation::Vertical, Alignment::Middle,
			viewSize / 2.f, *origin);

		delete origin;
	}

	void RecordTablePopUpState::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		popUpMenu->HandleWindowEvents(window, event);
	}

	void RecordTablePopUpState::Initialization(ResourceData& resourceData)
	{
		gameStateMachine->GetPointsService().SortRecords();

		SetTextData(*header, "Number of points", resourceData.font, 16);

		SetTextData(*pointsReceivedByThePlayer, "0", resourceData.font, 16);

		InitializeTheHighScoreTable(resourceData);

		MenuItem startGame;
		SetTextData(startGame.text, "Start game", resourceData.font, 24);
		startGame.onPressCallback = [this](MenuItem& item)
			{
				gameStateMachine->SwitchCurrentStateTo(new GameplayState(*this->gameStateMachine));
			};

		MenuItem exitGame;
		SetTextData(exitGame.text, "Exit to menu", resourceData.font, 24);
		exitGame.onPressCallback = [this](MenuItem& item)
			{
				gameStateMachine->SwitchCurrentStateTo(new MainMenuState());
			};

		MenuItem mainMenu;
		SetChildrenData(mainMenu, Orientation::Vertical, Alignment::Middle, 10.f);
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(exitGame);

		popUpMenu->Initialization(mainMenu);
	}

	void RecordTablePopUpState::Update(float deltaTime, sf::RenderWindow& window)
	{
	}

	void RecordTablePopUpState::InitializeTheHighScoreTable(ResourceData& resourceData)
	{
		popUpTableTexts->clear();

		popUpTableTexts->push_back(header);
		popUpTableTexts->push_back(pointsReceivedByThePlayer);

		std::map<std::string, unsigned int>& map = gameStateMachine->GetPointsService().GetRecordsTable();

		int count = 0;
		for (auto& value : map)
		{
			if (count >= GAMEOVER_RECORD_TABLE_QUANTITY_LIMIT)
			{
				break;
			}

			sf::Text* record = new sf::Text();

			SetTextData(*record, value.first + " - " + std::to_string(value.second), resourceData.font, 16);

			popUpTableTexts->push_back(record);

			++count;
		}
	}
}