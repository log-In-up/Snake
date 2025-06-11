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
		WALL = "Wall.png",
		SNAKE_BODY = "Body.png",
		SNAKE_BODY_BEND = "BodyBend.png",
		SNAKE_HEAD = "Head.png",
		SNAKE_TAIL = "Tail.png";

	const std::string FONT = "Roboto-Bold.ttf";

	const std::string START_SESSION = "Start_Session.wav",
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
		sf::Texture wall;
		sf::Texture snakeBody;
		sf::Texture snakeBodyBend;
		sf::Texture snakeHead;
		sf::Texture snakeTail;

		// Audio objects
		sf::SoundBuffer eatAppleBuffer;
		sf::Sound eatApple;
		sf::SoundBuffer backgroundBuffer;
		sf::Sound background;
		sf::SoundBuffer deathBuffer;
		sf::Sound death;
		sf::SoundBuffer loseBuffer;
		sf::Sound lose;
		sf::SoundBuffer menuBuffer;
		sf::Sound menu;
		sf::SoundBuffer snakeHitBuffer;
		sf::Sound snakeHit;
		sf::SoundBuffer startSessionBuffer;
		sf::Sound startSession;

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