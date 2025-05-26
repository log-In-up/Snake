#include "Sprite.h"

namespace Snake
{
	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
	{
		const auto distance = sprite1.getPosition() - sprite2.getPosition();
		if (sqrtf(distance.x * distance.x + distance.y * distance.y) * 2 < sprite1.getGlobalBounds().width + sprite2.getGlobalBounds().width)
		{
			return true;
		}
		return false;
	}

	void DrawSprite(const sf::Sprite& sprite, sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		SetSpriteSize(sprite, desiredWidth, desiredHeight);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}
}