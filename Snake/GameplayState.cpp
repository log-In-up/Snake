#include "AppleService.h"
#include "EnterNamePopUpState.h"
#include "GameplayState.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "NoPopUp.h"
#include "PointsService.h"
#include "PopUpStateMachine.h"
#include "Snake.h"
#include "Sprite.h"
#include "Text.h"
#include "TextMenu.h"
#include "TimeService.h"
#include "WallCreator.h"

namespace Snake
{
	TextMenu* gameplayTextMenu;
	SnakeData* snakeData;
	Snake* snake;
	AppleService* appleService;
	WallCreator* wallCreator;
	PopUpStateMachine* popUpStateMachine;
	GameplayData* gameplayData;

	float* elapsedTime;
	float* prePauseTime;

	GameplayState::GameplayState(GameStateMachine& gameStateMachine) : GameState()
	{
		gameplayData = new GameplayData();
		gameplayData->isGameOver = false;

		gameplayTextMenu = new TextMenu(gameStateMachine.GetAudioService());
		snakeData = new SnakeData();
		snake = new Snake(*snakeData);
		appleService = new AppleService();
		wallCreator = new WallCreator();
		popUpStateMachine = new PopUpStateMachine(gameStateMachine);

		elapsedTime = new float(0.f);
		prePauseTime = new float(GAME_PRE_PAUSE_TIME);
	}

	GameplayState::~GameplayState()
	{
		delete gameplayData;
		delete gameplayTextMenu;
		delete snakeData;
		delete snake;
		delete appleService;
		delete wallCreator;
		delete popUpStateMachine;

		delete elapsedTime;
		delete prePauseTime;
	}

	void GameplayState::Draw(sf::RenderWindow& window)
	{
		DrawSprites(snakeData->body.begin(), snakeData->body.end(), window);

		appleService->Draw(window);
		wallCreator->Draw(window);
		popUpStateMachine->Draw(window);

		if (!gameplayData->isGameOver && TimeIsPaused())
		{
			sf::Vector2f* origin = new sf::Vector2f(0.5f, 0.f);

			gameplayTextMenu->Draw(window, *origin, 150.f);

			delete origin;
		}

		gameStateMachine->GetPointsService().Draw(window);
	}

	void GameplayState::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		popUpStateMachine->HandleWindowEvents(window, event);

		if (gameplayData->isGameOver)
		{
			return;
		}

		bool gameIsPaused = TimeIsPaused();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P)
			{
				SetPause(!gameIsPaused);
			}

			if (!gameIsPaused)
			{
				snake->ReadInput(event);
			}
		}

		if (gameIsPaused)
		{
			gameplayTextMenu->HandleWindowEvents(window, event);
		}
	}

	void GameplayState::Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService)
	{
		popUpStateMachine->SwitchCurrentStateTo(new NoPopUp());

		InitializationOfTheSnake(resourceData, difficultyService);
		GameplayTextMenuInitialization(resourceData);

		gameStateMachine->GetPointsService().Initialization(resourceData, difficultyService);
		appleService->Initialization(resourceData, difficultyService);

		wallCreator->CreateScreenPerimeterWalls(resourceData);
		appleService->CreateApple(snake->GetSnakeData().body);

		gameStateMachine->GetAudioService().PlayStartSession();
		gameStateMachine->GetAudioService().SetPlayBackground(true);

		SetPause(false);
	}

	void GameplayState::Update(float deltaTime, sf::RenderWindow& window)
	{
		if (gameplayData->isGameOver || GameIsOnPrePause(deltaTime))
		{
			return;
		}

		*elapsedTime += deltaTime;
		if (*elapsedTime < SNAKE_SIZE / snakeData->speed)
		{
			return;
		}

		snake->MoveSnake(deltaTime);

		if (CheckSpriteIntersection(*snake->GetSnakeData().head, appleService->GetAppleData().sprite))
		{
			gameStateMachine->GetAudioService().PlaySnakeHit();

			snake->GrowSnake();

			gameStateMachine->GetPointsService().AddPoints();

			appleService->CreateApple(snake->GetSnakeData().body);
		}

		*elapsedTime = 0.f;

		if (!gameplayData->isGameOver)
		{
			SnakeData& snakeData = snake->GetSnakeData();
			std::vector<sf::Sprite>& wall = wallCreator->GetWall();

			gameplayData->isGameOver = FullCheckCollisions(wall.begin(), wall.end(), *snakeData.head) ||
				FullCheckCollisions(snakeData.body.begin(), snakeData.head, *snakeData.head) ||
				FullCheckCollisions(std::next(snakeData.head), snakeData.body.end(), *snakeData.head);

			if (gameplayData->isGameOver)
			{
				gameStateMachine->GetAudioService().SetPlayBackground(false);
				gameStateMachine->GetAudioService().PlayLose();

				popUpStateMachine->SwitchCurrentStateTo(new EnterNamePopUpState(*gameStateMachine));
			}
		}
	}

	bool GameplayState::GameIsOnPrePause(float deltaTime)
	{
		if (*prePauseTime > 0.f)
		{
			*prePauseTime -= deltaTime;
			return true;
		}
		else
		{
			return false;
		}
	}

	void GameplayState::GameplayTextMenuInitialization(ResourceData& resourceData)
	{
		MenuItem exitTheGame;
		SetTextData(exitTheGame.text, "Exit the game", resourceData.font, 24);
		exitTheGame.onPressCallback = [this](MenuItem& item)
			{
				gameStateMachine->GetAudioService().SetPlayBackground(false);
				gameStateMachine->SwitchCurrentStateTo(new MainMenuState(*gameStateMachine));
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
	}

	void GameplayState::InitializationOfTheSnake(ResourceData& resourceData, GameDifficultyService& difficultyService)
	{
		snake->LoadSnakeTextures(resourceData);

		snake->Initialization(difficultyService.GetCurrentDifficultyData());
	}
}