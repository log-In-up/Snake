#include <SFML/Graphics/Text.hpp>

#include "PointsService.h"
#include "Text.h"
#include "Utils.h"

namespace Snake
{
	unsigned int currentPoints;
	unsigned int pointsPerApple;

	sf::Text* displayingTheNumberOfPoints;
	std::map<std::string, int>* recordsTable;

	PointsService::PointsService()
	{
		currentPoints = 0;
		pointsPerApple = 0;

		displayingTheNumberOfPoints = new sf::Text();

		recordsTable = new std::map<std::string, int>();
		recordsTable->insert(std::pair<std::string, int>("Carol", 55));
		recordsTable->insert(std::pair<std::string, int>("Jane", 30));
		recordsTable->insert(std::pair<std::string, int>("Alice", 120));
		recordsTable->insert(std::pair<std::string, int>("Bob", 85));
	}

	PointsService::~PointsService()
	{
		delete displayingTheNumberOfPoints;
		delete recordsTable;
	}

	std::map<std::string, int>& PointsService::GetRecordsTable()
	{
		return *recordsTable;
	}

	unsigned int PointsService::GetPoints()
	{
		return currentPoints;
	}

	void PointsService::AddPoints()
	{
		currentPoints += pointsPerApple;

		displayingTheNumberOfPoints->setString(std::to_string(currentPoints));
	}

	void PointsService::Draw(sf::RenderWindow& window)
	{
		displayingTheNumberOfPoints->setPosition((window.getSize().x - 40.f), 8.f);
		window.draw(*displayingTheNumberOfPoints);
	}

	void PointsService::Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService)
	{
		pointsPerApple = difficultyService.GetCurrentDifficultyData().pointsPerEatenApple;

		SetTextData(*displayingTheNumberOfPoints, std::to_string(currentPoints), resourceData.font, 16, sf::Color::White);
	}

	void PointsService::SortRecords()
	{
		SelectionSort(*recordsTable);
	}
}