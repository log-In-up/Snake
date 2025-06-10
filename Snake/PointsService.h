#pragma once
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "GameDifficultyService.h"
#include "ResourceLoader.h"

namespace Snake
{
	class PointsService
	{
	public:
		PointsService();
		~PointsService();
		std::map<std::string, unsigned int>& GetRecordsTable();
		unsigned int GetPoints();
		void AddPoints();
		void AddRecord(std::string name, unsigned int points);
		void Draw(sf::RenderWindow& window);
		void Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService);
		void SortRecords();
	};
}
