#include "Game.h"

namespace Snake
{
	Game::Game()
	{
	}

	Game::~Game()
	{
	}

	void Game::Draw(sf::RenderWindow& window)
	{
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
	}

	void Game::Initialization()
	{
	}

	void Game::Update(sf::RenderWindow& window)
	{
	}
}