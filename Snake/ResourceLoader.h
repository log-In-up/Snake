#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

namespace Snake
{
	const std::string RESOURCES_PATH = "Resources/";

	const std::string APPLE = "Textures\\Apple.png",
		ROCK = "Textures\\Rock.png",
		SNAKE_BODY = "Textures\\Body.png",
		SNAKE_BODY_BEND = "Textures\\BodyBend.png",
		SNAKE_HEAD = "Textures\\Head.png",
		SNAKE_TAIL = "Textures\\Tail.png";

	const std::string FONT = "Fonts\\Roboto-Bold.ttf";

	const std::string APPLE_EAT = "Sounds\\Apple_Eat.wav",
		BACKGROUND_MUSIC = "Sounds\\Clint_Hammer_Background_Music.wav",
		DEATH = "Sounds\\Death.wav",
		LOSE = "Sounds\\Maodin204_Lose.wav",
		MENU = "Sounds\\The_Evil_Socks_Menu_Hover.wav",
		SNAKE_HIT = "Sounds\\Owlstorm_Snake_Hit.wav";

	struct ResourceData
	{
		// Textures
		sf::Texture apple;
		sf::Texture rock;
		sf::Texture snakeBody;
		sf::Texture snakeBodyBend;
		sf::Texture snakeHead;
		sf::Texture snakeTail;

		// Audio objects
		sf::SoundBuffer soundBuffer;
		sf::Sound eatApple;
		sf::Sound background;
		sf::Sound death;
		sf::Sound lose;
		sf::Sound menu;
		sf::Sound snakeHit;

		// Fonts
		sf::Font font;
	};

	class ResourceLoader
	{
	public:
		void LoadResources(ResourceData& resourceData);
	private:
		void LoadFont(std::string resourceURL, sf::Font& font);
		void LoadSound(std::string resourceURL, sf::Sound& sound, sf::SoundBuffer& soundBuffer);
		void LoadTexture(std::string resourceURL, sf::Texture& texture);
	};
}