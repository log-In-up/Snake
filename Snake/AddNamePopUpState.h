#pragma once
#include <string>

#include "PopUpState.h"

namespace Snake
{
	const int ASCII_SIZE = 128, BACKSPACE_CODE = 8;
	const std::string DEFAULT_PLAYER_NAME = "XYZ";

	class AddNamePopUpState : public PopUpState
	{
	public:
		AddNamePopUpState();
		~AddNamePopUpState();

		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	};
}