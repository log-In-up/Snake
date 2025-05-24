#pragma once
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

namespace Snake
{
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText; // Visible when child item is selected
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing = 0.f;

		bool isEnabled = true;
		sf::Color selectedColor = sf::Color::Green;
		sf::Color deselectedColor = sf::Color::White;

		std::vector<MenuItem> childrens;

		std::function<void(MenuItem& item)> onPressCallback;

		MenuItem* parent = nullptr;
	};

	class TextMenu
	{
	private:
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;
	public:
		void Draw(sf::RenderWindow& window, sf::Vector2f& origin, float height);
		void GoBack();
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event);
		void Initialization(const MenuItem& item);
	private:
		MenuItem& GetCurrentContext();
		void InitMenuItem(MenuItem& item);
		void PressOnSelectedItem();
		void SelectMenuItem(MenuItem& item);
		void SwitchToNextMenuItem();
		void SwitchToPreviousMenuItem();
	};

	void SetChildrenData(MenuItem& item, Orientation orientation, Alignment alignment, float spacing);
}