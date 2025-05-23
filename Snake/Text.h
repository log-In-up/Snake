#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "TextMenu.h"

namespace Snake
{
	class Text
	{
	};

	void DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);
	void SetTextData(sf::Text& text, const std::string string, sf::Font& font, unsigned int size);
	void SetTextData(sf::Text& text, const std::string string, sf::Font& font, unsigned int size, const sf::Color color);
}