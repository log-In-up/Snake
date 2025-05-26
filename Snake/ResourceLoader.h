#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace Snake
{
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	const std::string APPLE = "Apple.png",
		ROCK = "Rock.png",
		SNAKE_BODY = "Body.png",
		SNAKE_BODY_BEND = "BodyBend.png",
		SNAKE_HEAD = "Head.png",
		SNAKE_TAIL = "Tail.png";

	const std::string FONT = "Roboto-Bold.ttf";

	const std::string APPLE_EAT = "Apple_Eat.wav",
		BACKGROUND_MUSIC = "Clint_Hammer_Background_Music.wav",
		DEATH = "Death.wav",
		LOSE = "Maodin204_Lose.wav",
		MENU = "The_Evil_Socks_Menu_Hover.wav",
		SNAKE_HIT = "Owlstorm_Snake_Hit.wav";

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