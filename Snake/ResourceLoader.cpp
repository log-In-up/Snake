#include <cassert>

#include "ResourceLoader.h"

namespace Snake
{
	void ResourceLoader::LoadResources(ResourceData& resourceData)
	{
		LoadFont(FONT, resourceData.font);

		LoadSound(BACKGROUND_MUSIC, resourceData.background, resourceData.backgroundBuffer);
		LoadSound(DEATH, resourceData.death, resourceData.deathBuffer);
		LoadSound(LOSE, resourceData.lose, resourceData.loseBuffer);
		LoadSound(MENU, resourceData.menu, resourceData.menuBuffer);
		LoadSound(SNAKE_HIT, resourceData.snakeHit, resourceData.snakeHitBuffer);
		LoadSound(START_SESSION, resourceData.startSession, resourceData.startSessionBuffer);

		LoadTexture(APPLE, resourceData.apple);
		LoadTexture(ROCK, resourceData.rock);
		LoadTexture(WALL, resourceData.wall);
		LoadTexture(SNAKE_BODY, resourceData.snakeBody);
		LoadTexture(SNAKE_BODY_BEND, resourceData.snakeBodyBend);
		LoadTexture(SNAKE_HEAD, resourceData.snakeHead);
		LoadTexture(SNAKE_TAIL, resourceData.snakeTail);
	}

	void ResourceLoader::LoadFont(std::string resourceURL, sf::Font& font)
	{
		if (font.loadFromFile(FONTS_PATH + resourceURL))
		{
		}
		else
		{
			assert(false);
		}
	}

	void ResourceLoader::LoadSound(std::string resourceURL, sf::Sound& sound, sf::SoundBuffer& soundBuffer)
	{
		if (soundBuffer.loadFromFile(SOUNDS_PATH + resourceURL))
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
		if (texture.loadFromFile(TEXTURES_PATH + resourceURL))
		{
		}
		else
		{
			assert(false);
		}
	}
}