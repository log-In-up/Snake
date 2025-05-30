#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameDifficultyService.h"

namespace Snake
{
	class PointsService
	{
	public:
		PointsService();
		~PointsService();
		void AddPoints();
		void Draw(sf::RenderWindow& window);
		void Initialization(GameDifficultyService& difficultyService);
	};
}
