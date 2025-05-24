#include "GameplayState.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "Text.h"
#include "TextMenu.h"
#include "TimeService.h"

namespace Snake
{
	TextMenu* gameplayTextMenu;

	GameplayState::GameplayState() : GameState()
	{
		gameplayTextMenu = new TextMenu();
	}

	GameplayState::~GameplayState()
	{
		delete gameplayTextMenu;
	}

	void GameplayState::Draw(sf::RenderWindow& window)
	{
		if (!TimeIsPaused())
		{
			return;
		}

		sf::Vector2f* origin = new sf::Vector2f(0.5f, 0.f);

		gameplayTextMenu->Draw(window, *origin, 150.f);

		delete origin;
	}

	void GameplayState::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		bool gameIsPaused = TimeIsPaused();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P)
			{
				SetPause(!gameIsPaused);
			}
		}

		if (gameIsPaused)
		{
			gameplayTextMenu->HandleWindowEvents(window, event);
		}
	}

	void GameplayState::Initialization(ResourceData& resourceData)
	{
		MenuItem exitTheGame;
		SetTextData(exitTheGame.text, "Exit the game", resourceData.font, 24);
		exitTheGame.onPressCallback = [this](MenuItem& item)
			{
				gameStateMachine->SwitchCurrentStateTo(new MainMenuState());
			};

		MenuItem continueGame;
		SetTextData(continueGame.text, "Continue", resourceData.font, 24);
		continueGame.onPressCallback = [this](MenuItem& item)
			{
				SetPause(false);
			};

		MenuItem pauseMenu;
		SetTextData(pauseMenu.hintText, "Pause", resourceData.font, 48, sf::Color::White);
		SetChildrenData(pauseMenu, Orientation::Vertical, Alignment::Middle, 10.f);
		pauseMenu.childrens.push_back(exitTheGame);
		pauseMenu.childrens.push_back(continueGame);

		gameplayTextMenu->Initialization(pauseMenu);

		SetPause(false);
	}

	void GameplayState::Update(float deltaTime, sf::RenderWindow& window)
	{
	}
}