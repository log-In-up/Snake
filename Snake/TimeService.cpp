#include <SFML/System/Clock.hpp>

#include "TimeService.h"

namespace Snake
{
	bool* gameIsOnPause;
	float* lastTime;
	sf::Clock* clock;

	TimeService::TimeService()
	{
		gameIsOnPause = new bool(false);
		lastTime = new float(0.f);
		clock = new sf::Clock();
	}

	TimeService::~TimeService()
	{
		delete gameIsOnPause;
		delete lastTime;
		delete clock;
	}

	float TimeService::GetDeltaTime()
	{
		float currentTime = clock->getElapsedTime().asSeconds();
		float deltaTime = gameIsOnPause ? ZERO_DELTA_TIME : currentTime - *lastTime;
		*lastTime = currentTime;

		return deltaTime;
	}

	void TimeService::Initialization()
	{
		*lastTime = clock->getElapsedTime().asSeconds();
	}

	bool& TimeIsPaused()
	{
		return *gameIsOnPause;
	}

	void SetPause(bool value)
	{
		*gameIsOnPause = value;
	}
}