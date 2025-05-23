#include "Game.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "ResourceLoader.h"
#include "TimeService.h"

namespace Snake
{
	GameStateMachine* gameStateMachine;
	ResourceData* resourceData;
	ResourceLoader* resourceLoader;
	TimeService* timeService;

	Game::Game()
	{
		resourceData = new ResourceData();
		gameStateMachine = new GameStateMachine(new MainMenuState(), *resourceData);
		resourceLoader = new ResourceLoader();
		timeService = new TimeService();
	}

	Game::~Game()
	{
		delete gameStateMachine;
		delete resourceData;
		delete resourceLoader;
		delete timeService;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		gameStateMachine->Draw(window);
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			gameStateMachine->HandleWindowEvents(window, event);
		}
	}

	void Game::Initialization()
	{
		resourceLoader->LoadResources(*resourceData);

		timeService->Initialization();

		gameStateMachine->Initialization();
	}

	void Game::Update(sf::RenderWindow& window)
	{
		float deltaTime = timeService->GetDeltaTime();

		gameStateMachine->Update(deltaTime, window);
	}
}