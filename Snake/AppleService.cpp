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

	void AppleService::CreateApple()
	{
		apple->position.x = (rand() % SCREEN_WIDTH);
		apple->position.y = (rand() % SCREEN_HEIGHT);

		apple->sprite.setPosition((float)apple->position.x, (float)apple->position.y);
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