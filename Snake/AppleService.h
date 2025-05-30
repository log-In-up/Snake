#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "GameDifficultyService.h"
#include "ResourceLoader.h"

namespace Snake
{
	const float APPLE_SIZE = 20.f;

	struct AppleData
	{
		sf::Vector2i position;
		sf::Sprite sprite;
	};

	class AppleService
	{
	private:
		AppleData* apple;
	public:
		AppleService();
		~AppleService();
		AppleData& GetAppleData();
		void CreateApple();
		void Draw(sf::RenderWindow& window);
		void Initialization(ResourceData& resourceData, GameDifficultyService& difficultyService);
	};
}