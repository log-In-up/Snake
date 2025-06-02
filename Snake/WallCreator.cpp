#include <math.h>
#include <SFML/Graphics/Sprite.hpp>

#include "GameMain.h"
#include "Sprite.h"
#include "WallCreator.h"

namespace Snake
{
	WallCreator::WallCreator()
	{
		wall = new std::vector<sf::Sprite>();
	}

	WallCreator::~WallCreator()
	{
		wall->clear();
		delete wall;
	}

	std::vector<sf::Sprite>& WallCreator::GetWall()
	{
		return *wall;
	}

	void WallCreator::CreateColumn(ResourceData& resourceData, unsigned int height, float width)
	{
		for (unsigned int index = 0; index < height; index++)
		{
			sf::Sprite sprite(resourceData.wall);
			SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
			SetSpriteSize(sprite, WALL_SIZE, WALL_SIZE);
			sprite.setPosition({ width ,WALL_SIZE * index });

			wall->push_back(sprite);
		}
	}

	void WallCreator::CreateRow(ResourceData& resourceData, unsigned int length, float height)
	{
		for (unsigned int index = 0; index < length; index++)
		{
			sf::Sprite sprite(resourceData.wall);
			sprite.setPosition({ WALL_SIZE * index, height });
			SetSpriteSize(sprite, WALL_SIZE, WALL_SIZE);

			wall->push_back(sprite);
		}
	}

	void WallCreator::CreateScreenPerimeterWalls(ResourceData& resourceData)
	{
		unsigned int length = (unsigned int)ceil(SCREEN_WIDTH / WALL_SIZE);

		CreateRow(resourceData, length, 0.f);
		CreateRow(resourceData, length, SCREEN_HEIGHT - WALL_SIZE);

		unsigned int height = (unsigned int)ceil(SCREEN_HEIGHT / WALL_SIZE);

		CreateColumn(resourceData, height, WALL_SIZE / 2);
		CreateColumn(resourceData, height, SCREEN_WIDTH - WALL_SIZE / 2);
	}

	void WallCreator::Draw(sf::RenderWindow& window)
	{
		DrawSprites(wall->begin(), wall->end(), window);
	}
}