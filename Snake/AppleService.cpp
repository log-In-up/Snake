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
		sf::FloatRect rect(0.f, 0.f, (float)(SCREEN_WIDTH - WALL_SIZE * 2), (float)(SCREEN_HEIGHT - WALL_SIZE * 2));
		SetSpriteRandomPosition(apple->sprite, rect, collection);
	}

	void AppleService::Draw(sf::RenderWindow& window)
	{
		window.draw(apple->sprite);
	}

	void AppleService::Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService)
	{
		apple->sprite.setTexture(resourceData.apple);

		SetSpriteRelativeOrigin(apple->sprite, 0.f, 0.5f);
		SetSpriteSize(apple->sprite, APPLE_SIZE, APPLE_SIZE);
	}
}