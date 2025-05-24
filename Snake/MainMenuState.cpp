#include <SFML/System/Vector2.hpp>

#include "CloseApplication.h"
#include "GameplayState.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "Text.h"
#include "TextMenu.h"

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
		mainTextMenu->Draw(window, *new sf::Vector2f(0.5f, 0.f), 150.f);
	}

	void MainMenuState::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		mainTextMenu->HandleWindowEvents(window, event);
	}

	void MainMenuState::Initialization(ResourceData& resourceData)
	{
		MenuItem startGame;
		SetTextData(startGame.text, "Start the game", resourceData.font, 24);
		startGame.onPressCallback = [this](MenuItem& item)
			{
				gameStateMachine->SwitchCurrentStateTo(new GameplayState());
			};

		MenuItem difficultyLevel;
		SetTextData(difficultyLevel.text, "Difficulty level", resourceData.font, 24);
		SetTextData(difficultyLevel.hintText, "Difficulty level", resourceData.font, 48, sf::Color::White);
		difficultyLevel.onPressCallback = [this](MenuItem& item)
			{
			};

		MenuItem tableOfRecords;
		SetTextData(tableOfRecords.text, "Table of records", resourceData.font, 24);
		tableOfRecords.onPressCallback = [this](MenuItem& item)
			{
			};

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
}