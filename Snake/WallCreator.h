#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "ResourceLoader.h"

namespace Snake
{
	const float WALL_SIZE = 20.f;

	class WallCreator
	{
	private:
		std::vector<sf::Sprite>* wall;
	public:
		WallCreator();
		~WallCreator();
		std::vector<sf::Sprite>& GetWall();
		void CreateColumn(ResourceData& resourceData, unsigned int height, float width);
		void CreateRow(ResourceData& resourceData, unsigned int length, float height);
		void CreateScreenPerimeterWalls(ResourceData& resourceData);
		void Draw(sf::RenderWindow& window);
	};
}