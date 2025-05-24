#include "CloseApplication.h"

namespace Snake
{
	CloseApplication::CloseApplication() : GameState()
	{
	}

	CloseApplication::~CloseApplication()
	{
	}

	void CloseApplication::Draw(sf::RenderWindow& window)
	{
	}

	void CloseApplication::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		window.close();
	}

	void CloseApplication::Initialization(ResourceData& resourceData)
	{
	}

	void CloseApplication::Update(float deltaTime, sf::RenderWindow& window)
	{
	}
}