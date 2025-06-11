#include <SFML/Graphics/Rect.hpp>

#include "AppleService.h"
#include "GameMain.h"
#include "Sprite.h"

namespace Snake
{
	AppleService::AppleService()
	{
		apple = new AppleData();
	}

	AppleService::~AppleService()
	{
		delete apple;
	}

	AppleData& AppleService::GetAppleData()
	{
		return *apple;
	}

	void AppleService::CreateApple(const std::list<sf::Sprite>& collection)
	{
		sf::FloatRect rect(WALL_SIZE, WALL_SIZE, (float)(SCREEN_WIDTH - WALL_SIZE), (float)(SCREEN_HEIGHT - WALL_SIZE));
		SetSpriteRandomPosition(apple->sprite, rect, collection, APPLE_SIZE);
	}

	void AppleService::Draw(sf::RenderWindow& window)
	{
		window.draw(apple->sprite);
	}

	void AppleService::Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService)
	{
		apple->sprite.setTexture(resourceData.apple);

		SetSpriteRelativeOrigin(apple->sprite, 0.5f, 0.5f);
		SetSpriteSize(apple->sprite, APPLE_SIZE, APPLE_SIZE);
	}
}