#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameDifficultyService.h"
#include "ResourceLoader.h"

namespace Snake
{
	class PointsService
	{
	public:
		PointsService();
		~PointsService();
		void AddPoints();
		void Draw(sf::RenderWindow& window);
		void Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService);
	};
}
