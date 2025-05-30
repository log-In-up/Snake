#include "GameDifficultyService.h"

namespace Snake
{
	GameDifficultyService::GameDifficultyService()
	{
		difficultyLevels = new std::vector<DifficultyData*>();

		difficultyLevels->push_back(new DifficultyData("Easy", 15.f, 2));
		difficultyLevels->push_back(new DifficultyData("Harder than Easy", 30.f, 4));
		difficultyLevels->push_back(new DifficultyData("Medium", 45.f, 6));
		difficultyLevels->push_back(new DifficultyData("Easier than Hard", 60.f, 8));
		difficultyLevels->push_back(new DifficultyData("Hard", 75.f, 10));

		currentDifficultyData = difficultyLevels->at(0);
	}

	GameDifficultyService::~GameDifficultyService()
	{
		difficultyLevels->clear();
		delete difficultyLevels;
	}

	DifficultyData& GameDifficultyService::GetCurrentDifficultyData()
	{
		return *currentDifficultyData;
	}

	std::vector<DifficultyData*>& GameDifficultyService::GetDifficultyLevels()
	{
		return *difficultyLevels;
	}

	void GameDifficultyService::SetCurrentDifficultyData(DifficultyData* difficultyData)
	{
		currentDifficultyData = difficultyData;
	}
}