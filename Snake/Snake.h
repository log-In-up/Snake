#pragma once
#include <array>
#include <list>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "GameDifficultyService.h"
#include "ResourceLoader.h"

namespace Snake
{
	const float SNAKE_SIZE = 20.f;
	const unsigned int INITIAL_SNAKE_SIZE = 3;
	const float INITIAL_SPEED = 200.f;
	const float ACCELERATION = 10.f;

	enum class SnakeDirection
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	enum class SnakePart : uint8_t
	{
		Head = 0,
		Body,
		BodyBend,
		Tail,
		Count
	};

	struct SnakeData
	{
		std::list<sf::Sprite> body;
		std::list<sf::Sprite>::iterator head;
		std::list<sf::Sprite>::iterator tail;
		float speed = 0.f; // Pixels per second
		SnakeDirection direction = SnakeDirection::Up;
		std::array<sf::Texture, (size_t)SnakePart::Count> textures;
	};

	class Snake
	{
	private:
		SnakeData& snakeData;
	public:
		Snake(SnakeData& snakeData);
		~Snake();
		SnakeData& GetSnakeData();
		void GrowSnake();
		void Initialization(DifficultyData& difficultyData);
		void LoadSnakeTextures(ResourceData& resourceData);
		void MoveSnake(float deltaTime);
	private:
		sf::Vector2f GetDirectionVector(SnakeDirection direction);
	};

	bool CheckSnakeCollisionWithHimself(SnakeData& snakeData);
	bool HasSnakeCollisionWithScreenBorder(const SnakeData& snakeData, const sf::FloatRect& rect);
}