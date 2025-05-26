#include "GameplayState.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "Snake.h"
#include "Sprite.h"
#include "Text.h"
#include "TextMenu.h"
#include "TimeService.h"

namespace Snake
{
	TextMenu* gameplayTextMenu;
	SnakeData* snakeData;
	Snake* snake;

	float* elapsedTime;

	GameplayState::GameplayState() : GameState()
	{
		gameplayTextMenu = new TextMenu();
		snakeData = new SnakeData();
		snake = new Snake(*snakeData);
		elapsedTime = new float(0.f);
	}

	GameplayState::~GameplayState()
	{
		delete gameplayTextMenu;
		delete snakeData;
		delete snake;
		delete elapsedTime;
	}

	void GameplayState::Draw(sf::RenderWindow& window)
	{
		DrawSprites(snakeData->body.begin(), snakeData->body.end(), window);

		if (TimeIsPaused())
		{
			sf::Vector2f* origin = new sf::Vector2f(0.5f, 0.f);

			gameplayTextMenu->Draw(window, *origin, 150.f);

			delete origin;
		}
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

			if (!gameIsPaused)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					snakeData->direction = SnakeDirection::Up;
					break;
				case sf::Keyboard::A:
					snakeData->direction = SnakeDirection::Left;
					break;
				case sf::Keyboard::S:
					snakeData->direction = SnakeDirection::Down;
					break;
				case sf::Keyboard::D:
					snakeData->direction = SnakeDirection::Right;
					break;
				default:
					break;
				}
			}
		}

		if (gameIsPaused)
		{
			gameplayTextMenu->HandleWindowEvents(window, event);
		}
	}

	void GameplayState::Initialization(ResourceData& resourceData)
	{
		*elapsedTime = 0.f;

		InitializationOfTheSnake(resourceData);

		GameplayTextMenuInitialization(resourceData);

		SetPause(false);
	}

	void GameplayState::Update(float deltaTime, sf::RenderWindow& window)
	{
		*elapsedTime += deltaTime;
		if (*elapsedTime < SNAKE_SIZE / snakeData->speed) {
			return;
		}

		snake->MoveSnake(deltaTime);

		*elapsedTime = 0.f;
	}

	void GameplayState::GameplayTextMenuInitialization(ResourceData& resourceData)
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
	}

	void GameplayState::InitializationOfTheSnake(ResourceData& resourceData)
	{
		snakeData->textures[(size_t)SnakePart::Head] = resourceData.snakeHead;
		snakeData->textures[(size_t)SnakePart::Body] = resourceData.snakeBody;
		snakeData->textures[(size_t)SnakePart::BodyBend] = resourceData.snakeBodyBend;
		snakeData->textures[(size_t)SnakePart::Tail] = resourceData.snakeTail;

		snake->Initialization();
	}
}