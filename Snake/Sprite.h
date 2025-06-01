#pragma once
#include <list>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Snake
{
	class Sprite
	{
	};

	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
	sf::Vector2f GetRandomSpritePositionInRectangle(const sf::Sprite& sprite, const sf::FloatRect& rect);
	void DrawSprite(const sf::Sprite& sprite, sf::RenderWindow& window);
	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture);
	void SetSpriteRandomPosition(sf::Sprite& sprite, const sf::FloatRect& rect, const std::list<sf::Sprite>& collection);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	template<class InputIt>
	bool FullCheckCollisions(InputIt first, const InputIt last, const sf::Sprite& sprite) {
		for (; first != last; ++first) {
			if (CheckSpriteIntersection(*first, sprite)) {
				return true;
			}
		}
		return false;
	}

	template<class InputIt>
	void DrawSprites(InputIt first, const InputIt last, sf::RenderWindow& window) {
		for (; first != last; ++first) {
			DrawSprite(*first, window);
		}
	}
}