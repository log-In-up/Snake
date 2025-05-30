#include <SFML/System/Vector2.hpp>

#include "CloseApplication.h"
#include "GameDifficultyService.h"
#include "GameplayState.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "Text.h"

namespace Snake
{
	TextMenu* mainTextMenu;

	MainMenuState::MainMenuState() : GameState()
	{
		mainTextMenu = new TextMenu();
	}

	MainMenuState::~MainMenuState()
	{
		delete mainTextMenu;
	}

	void MainMenuState::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f* origin = new sf::Vector2f(0.5f, 0.f);

		mainTextMenu->Draw(window, *origin, 150.f);

		delete origin;
	}

	void MainMenuState::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		mainTextMenu->HandleWindowEvents(window, event);
	}

	void MainMenuState::Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService)
	{
		MenuItem startGame;
		SetTextData(startGame.text, "Start the game", resourceData.font, 24);
		startGame.onPressCallback = [this](MenuItem& item)
			{
				gameStateMachine->SwitchCurrentStateTo(new GameplayState());
			};

		std::vector<MenuItem> difficultiesList = GetAListOfDifficulties(resourceData, difficultyService);

		MenuItem difficultyLevel;
		SetTextData(difficultyLevel.text, "Difficulty level", resourceData.font, 24);
		SetTextData(difficultyLevel.hintText, "Difficulty level", resourceData.font, 48, sf::Color::White);
		SetChildrenData(difficultyLevel, Orientation::Vertical, Alignment::Middle, 10.f);
		difficultyLevel.childrens.insert(difficultyLevel.childrens.begin(), difficultiesList.begin(), difficultiesList.end());

		MenuItem tableOfRecords;
		SetTextData(tableOfRecords.text, "Table of records", resourceData.font, 24);
		SetTextData(tableOfRecords.hintText, "Table of records", resourceData.font, 48, sf::Color::White);

		MenuItem sound;
		SetTextData(sound.text, "Sound [ ]", resourceData.font, 24);
		sound.onPressCallback = [](MenuItem& item)
			{
			};

		MenuItem music;
		SetTextData(music.text, "Music [ ]", resourceData.font, 24);
		music.onPressCallback = [](MenuItem& item)
			{
			};

		MenuItem settings;
		SetTextData(settings.text, "Settings", resourceData.font, 24);
		SetTextData(settings.hintText, "Settings", resourceData.font, 48, sf::Color::White);
		SetChildrenData(settings, Orientation::Vertical, Alignment::Middle, 10.f);
		settings.childrens.push_back(sound);
		settings.childrens.push_back(music);

		MenuItem yes;
		SetTextData(yes.text, "Yes", resourceData.font, 24);
		yes.onPressCallback = [this](MenuItem& item)
			{
				gameStateMachine->SwitchCurrentStateTo(new CloseApplication());
			};

		MenuItem no;
		SetTextData(no.text, "No", resourceData.font, 24);
		no.onPressCallback = [this](MenuItem& item)
			{
				mainTextMenu->GoBack();
			};

		MenuItem exitGame;
		SetTextData(exitGame.text, "Exit Game", resourceData.font, 24);
		SetTextData(exitGame.hintText, "Are you sure?", resourceData.font, 48, sf::Color::White);
		SetChildrenData(exitGame, Orientation::Horizontal, Alignment::Middle, 10.f);
		exitGame.childrens.push_back(yes);
		exitGame.childrens.push_back(no);

		MenuItem mainMenu;
		SetTextData(mainMenu.hintText, "Snake", resourceData.font, 48, sf::Color::White);
		SetChildrenData(mainMenu, Orientation::Vertical, Alignment::Middle, 10.f);
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(difficultyLevel);
		mainMenu.childrens.push_back(tableOfRecords);
		mainMenu.childrens.push_back(settings);
		mainMenu.childrens.push_back(exitGame);

		mainTextMenu->Initialization(mainMenu);
	}

	void MainMenuState::Update(float deltaTime, sf::RenderWindow& window)
	{
	}

	std::vector<MenuItem> MainMenuState::GetAListOfDifficulties(ResourceData& resourceData, GameDifficultyService& difficultyService)
	{
		std::vector<MenuItem>* result = new std::vector<MenuItem>();

		DifficultyData currentDifficulty = difficultyService.GetCurrentDifficultyData();

		for (DifficultyData* difficultyData : difficultyService.GetDifficultyLevels())
		{
			std::string value = (currentDifficulty.difficultyName == difficultyData->difficultyName) ? (std::string)"x" : (std::string)" ";

			MenuItem menuItem;
			SetTextData(menuItem.text, difficultyData->difficultyName, resourceData.font, 24);
			menuItem.onPressCallback = [difficultyData, result, currentDifficulty, &difficultyService](MenuItem& item)
				{
					difficultyService.SetCurrentDifficultyData(difficultyData);
				};

			result->push_back(menuItem);
		}

		return *result;
	}
}