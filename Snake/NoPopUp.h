#pragma once
#include "PopUpState.h"

namespace Snake
{
	class NoPopUp : public PopUpState
	{
	public:
		NoPopUp();
		~NoPopUp();

		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvents(sf::RenderWindow& window, sf::Event& event) override;
		void Initialization(ResourceData& resourceData) override;
		void Update(float deltaTime, sf::RenderWindow& window) override;
	};
}