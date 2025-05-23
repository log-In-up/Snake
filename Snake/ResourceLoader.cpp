#include <cassert>

#include "ResourceLoader.h"

namespace Snake
{
	void ResourceLoader::LoadResources(ResourceData& resourceData)
	{
		LoadFont(FONT, resourceData.font);

		LoadSound(APPLE_EAT, resourceData.eatApple, resourceData.soundBuffer);
		LoadSound(BACKGROUND_MUSIC, resourceData.background, resourceData.soundBuffer);
		LoadSound(DEATH, resourceData.death, resourceData.soundBuffer);
		LoadSound(LOSE, resourceData.lose, resourceData.soundBuffer);
		LoadSound(MENU, resourceData.menu, resourceData.soundBuffer);
		LoadSound(SNAKE_HIT, resourceData.snakeHit, resourceData.soundBuffer);

		LoadTexture(APPLE, resourceData.apple);
		LoadTexture(ROCK, resourceData.rock);
		LoadTexture(SNAKE_BODY, resourceData.snakeBody);
		LoadTexture(SNAKE_BODY_BEND, resourceData.snakeBodyBend);
		LoadTexture(SNAKE_HEAD, resourceData.snakeHead);
		LoadTexture(SNAKE_TAIL, resourceData.snakeTail);
	}

	void ResourceLoader::LoadFont(std::string resourceURL, sf::Font& font)
	{
		if (font.loadFromFile(RESOURCES_PATH + resourceURL))
		{
		}
		else
		{
			assert(false);
		}
	}

	void ResourceLoader::LoadSound(std::string resourceURL, sf::Sound& sound, sf::SoundBuffer& soundBuffer)
	{
		if (soundBuffer.loadFromFile(RESOURCES_PATH + resourceURL))
		{
			sound.setBuffer(soundBuffer);
		}
		else
		{
			assert(false);
		}
	}

	void ResourceLoader::LoadTexture(std::string resourceURL, sf::Texture& texture)
	{
		if (texture.loadFromFile(RESOURCES_PATH + resourceURL))
		{
		}
		else
		{
			assert(false);
		}
	}
}