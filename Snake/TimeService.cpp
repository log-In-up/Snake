#include <SFML/System/Clock.hpp>

#include "TimeService.h"

namespace Snake
{
	bool gameIsOnPause;
	float lastTime;
	sf::Clock clock;

	TimeService::TimeService()
	{
		gameIsOnPause = false;
		lastTime = 0.f;
		clock = sf::Clock();
	}

	TimeService::~TimeService()
	{
	}

	float TimeService::GetDeltaTime()
	{
		float currentTime = clock.getElapsedTime().asSeconds();
		float deltaTime = gameIsOnPause ? ZERO_DELTA_TIME : currentTime - lastTime;
		lastTime = currentTime;

		return deltaTime;
	}

	void TimeService::Initialization()
	{
		lastTime = clock.getElapsedTime().asSeconds();
	}

	bool TimeIsPaused()
	{
		return gameIsOnPause;
	}

	void SetPause(bool value)
	{
		gameIsOnPause = value;
	}
}