#include "PointsService.h"

namespace Snake
{
	unsigned int currentPoints;
	unsigned int pointsPerApple;

	PointsService::PointsService()
	{
		currentPoints = 0;
		pointsPerApple = 0;
	}

	PointsService::~PointsService()
	{
	}

	void PointsService::AddPoints()
	{
		currentPoints += pointsPerApple;
	}

	void PointsService::Draw(sf::RenderWindow& window)
	{
	}

	void PointsService::Initialization(GameDifficultyService& difficultyService)
	{
		pointsPerApple = difficultyService.GetCurrentDifficultyData().pointsPerEatenApple;
	}
}