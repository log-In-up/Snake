#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "PointsService.h"
#include "TextMenu.h"

namespace Snake
{
	class PopUpWindow
	{
	private:
		PointsService& pointsService;
	public:
		PopUpWindow(PointsService& pointsService);
		~PopUpWindow();
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event);
		void Initialization(const MenuItem item, ResourceData& resourceData);
		void UpdatePop();
	};
}