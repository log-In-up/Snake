#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace Snake
{
	class Mathematics
	{
	};

	sf::Vector2f GetTextOrigin(sf::Text& text, const sf::Vector2f& relativePosition);
}
