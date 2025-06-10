#include "GameMain.h"
#include "Snake.h"
#include "Sprite.h"

namespace Snake
{
	static std::list<sf::Sprite>::iterator GetNextIterator(SnakeData& snake, std::list<sf::Sprite>::iterator it)
	{
		auto nextIt = std::next(it);
		if (nextIt == snake.body.end())
		{
			nextIt = snake.body.begin();
		}
		return nextIt;
	}

	static std::list<sf::Sprite>::iterator GetPrevIterator(SnakeData& snake, std::list<sf::Sprite>::iterator it)
	{
		auto prevIt = it == snake.body.begin() ?
			std::prev(snake.body.end()) :
			std::prev(it);

		return prevIt;
	}

	static void SetHeadSprite(SnakeData& snake, std::list<sf::Sprite>::iterator it)
	{
		auto prevIt = GetPrevIterator(snake, it);
		float angle = -90.f; // Left
		if (prevIt->getPosition().y > it->getPosition().y)
		{
			// Up
			angle = 0.f;
		}
		else if (prevIt->getPosition().x < it->getPosition().x)
		{
			// Right
			angle = 90.f;
		}
		else if (prevIt->getPosition().y < it->getPosition().y)
		{
			// Down
			angle = 180.f;
		}

		it->setTexture(snake.textures[(size_t)SnakePart::Head]);
		it->setRotation(angle);
	}

	static void SetTailSprite(SnakeData& snake, std::list<sf::Sprite>::iterator it)
	{
		auto nextIt = GetNextIterator(snake, it);
		float angle = -90.f; // Left
		if (nextIt->getPosition().y > it->getPosition().y)
		{
			// Up
			angle = 0.f;
		}
		else if (nextIt->getPosition().x < it->getPosition().x)
		{
			// Right
			angle = 90.f;
		}
		else if (nextIt->getPosition().y < it->getPosition().y)
		{
			// Down
			angle = 180.f;
		}

		it->setTexture(snake.textures[(size_t)SnakePart::Tail]);
		it->setRotation(angle);
	}

	static void SetBodySprite(SnakeData& snake, std::list<sf::Sprite>::iterator it)
	{
		auto prevIt = GetPrevIterator(snake, it);
		auto nextIt = GetNextIterator(snake, it);
		float angle = 0.f; // Left
		sf::Texture* texturePtr = &snake.textures[(size_t)SnakePart::BodyBend];;

		if (prevIt->getPosition().x == nextIt->getPosition().x || prevIt->getPosition().y == nextIt->getPosition().y)
		{
			// Hor or Ver
			texturePtr = &snake.textures[(size_t)SnakePart::Body];
			angle = prevIt->getPosition().x != nextIt->getPosition().x ? 90.f : 0.f;
		}
		else
		{
			if (prevIt->getPosition().x < it->getPosition().x && it->getPosition().y > nextIt->getPosition().y ||
				prevIt->getPosition().y < it->getPosition().y && it->getPosition().x > nextIt->getPosition().x)
			{
				// dir: right -> up or down -> left
				angle = 0.f;
			}
			else if (prevIt->getPosition().y < it->getPosition().y && it->getPosition().x < nextIt->getPosition().x ||
				prevIt->getPosition().x > it->getPosition().x && it->getPosition().y > nextIt->getPosition().y)
			{
				// dir: down -> right or left -> up
				angle = 90.f;
			}
			else if (prevIt->getPosition().x > it->getPosition().x && it->getPosition().y < nextIt->getPosition().y ||
				prevIt->getPosition().y > it->getPosition().y && it->getPosition().x < nextIt->getPosition().x)
			{
				// dir: left -> down or up -> right
				angle = 180.f;
			}
			else if (prevIt->getPosition().y > it->getPosition().y && it->getPosition().x > nextIt->getPosition().x ||
				prevIt->getPosition().x < it->getPosition().x && it->getPosition().y < nextIt->getPosition().y)
			{
				// dir: up -> left or right -> down
				angle = -90.f;
			}
		}

		it->setTexture(*texturePtr);
		it->setRotation(angle);
	}

	Snake::Snake(SnakeData& snakeData) : snakeData(snakeData)
	{
	}

	Snake::~Snake()
	{
	}

	SnakeData& Snake::GetSnakeData()
	{
		return snakeData;
	}

	void Snake::GrowSnake()
	{
		auto prevHead = snakeData.head;

		sf::Sprite sprite = *snakeData.head;
		sprite.setPosition(snakeData.head->getPosition() + GetDirectionVector(snakeData.direction));
		snakeData.head = snakeData.body.insert(++snakeData.head, sprite);

		// Set correct sprite for new part of body
		SetBodySprite(snakeData, prevHead);
	}

	void Snake::Initialization(DifficultyData& difficultyData)
	{
		// Init snake state
		for (int snakeSegmentIndex = 0; snakeSegmentIndex < INITIAL_SNAKE_SIZE; ++snakeSegmentIndex)
		{
			sf::Sprite sprite;

			if (!snakeSegmentIndex)
			{
				InitSprite(sprite, SNAKE_SIZE, SNAKE_SIZE, snakeData.textures[(size_t)SnakePart::Head]);
			}
			else if (snakeSegmentIndex + 1 == INITIAL_SNAKE_SIZE)
			{
				InitSprite(sprite, SNAKE_SIZE, SNAKE_SIZE, snakeData.textures[(size_t)SnakePart::Tail]);
			}
			else
			{
				InitSprite(sprite, SNAKE_SIZE, SNAKE_SIZE, snakeData.textures[(size_t)SnakePart::Body]);
			}

			sprite.setPosition({ (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEIGHT / 2.f + SNAKE_SIZE * snakeSegmentIndex });
			snakeData.body.push_front(sprite);
		}
		snakeData.head = --snakeData.body.end();
		snakeData.tail = snakeData.body.begin();

		snakeData.speed = difficultyData.snakeMovementSpeed;
		snakeData.direction = SnakeDirection::Up;

		SetTailSprite(snakeData, snakeData.tail);
	}

	void Snake::LoadSnakeTextures(ResourceData& resourceData)
	{
		snakeData.textures[(size_t)SnakePart::Head] = resourceData.snakeHead;
		snakeData.textures[(size_t)SnakePart::Body] = resourceData.snakeBody;
		snakeData.textures[(size_t)SnakePart::BodyBend] = resourceData.snakeBodyBend;
		snakeData.textures[(size_t)SnakePart::Tail] = resourceData.snakeTail;
	}

	void Snake::MoveSnake(float deltaTime)
	{
		const sf::Vector2f direction = GetDirectionVector(snakeData.direction);
		auto prevHead = snakeData.head;

		snakeData.tail->setPosition(snakeData.head->getPosition() + direction);
		snakeData.head = snakeData.tail;
		snakeData.tail = GetNextIterator(snakeData, snakeData.tail);

		// Update textures
		SetHeadSprite(snakeData, snakeData.head);
		SetTailSprite(snakeData, snakeData.tail);
		SetBodySprite(snakeData, prevHead);
	}

	void Snake::ReadInput(sf::Event& event)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::W:
			snakeData.direction = SnakeDirection::Up;
			break;
		case sf::Keyboard::A:
			snakeData.direction = SnakeDirection::Left;
			break;
		case sf::Keyboard::S:
			snakeData.direction = SnakeDirection::Down;
			break;
		case sf::Keyboard::D:
			snakeData.direction = SnakeDirection::Right;
			break;
		default:
			break;
		}
	}

	sf::Vector2f Snake::GetDirectionVector(SnakeDirection direction)
	{
		sf::Vector2f result;

		switch (direction)
		{
		case SnakeDirection::Up:
			result = { 0.f, -SNAKE_SIZE };
			break;
		case SnakeDirection::Right:
			result = { SNAKE_SIZE, 0.f };
			break;
		case SnakeDirection::Down:
			result = { 0.f, SNAKE_SIZE };
			break;
		case SnakeDirection::Left:
			result = { -SNAKE_SIZE, 0.f };
			break;
		}

		return result;
	}

	bool CheckSnakeCollisionWithHimself(SnakeData& snakeData)
	{
		return FullCheckCollisions(snakeData.body.begin(), snakeData.head, *snakeData.head) ||
			FullCheckCollisions(std::next(snakeData.head), snakeData.body.end(), *snakeData.head);
	}

	bool HasSnakeCollisionWithScreenBorder(const SnakeData& snakeData, const sf::FloatRect& rect)
	{
		return !rect.contains(snakeData.head->getPosition());
	}
}