#pragma once
#include <string>
#include <vector>

namespace Snake
{
	struct DifficultyData
	{
		DifficultyData(std::string name, float speed, unsigned int pointsPerApple) : difficultyName(name), snakeMovementSpeed(speed), pointsPerEatenApple(pointsPerApple)
		{
		}

		std::string difficultyName = "";
		float snakeMovementSpeed = 0.f;
		unsigned int pointsPerEatenApple = 0;
	};

	class GameDifficultyService
	{
	private:
		std::vector<DifficultyData*>* difficultyLevels;
		DifficultyData* currentDifficultyData;
	public:
		GameDifficultyService();
		~GameDifficultyService();
		DifficultyData& GetCurrentDifficultyData();
		std::vector<DifficultyData*>& GetDifficultyLevels();
		void SetCurrentDifficultyData(DifficultyData* difficultyData);
	};
}