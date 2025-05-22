#include "Game.h"
#include "GameMain.h"

int main()
{
	sf::VideoMode* videoMode = new sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BITS_PER_PIXEL);
	sf::RenderWindow* window = new sf::RenderWindow(*videoMode, TITLE);
	sf::Event* event = new sf::Event();

	Snake::Game* game = new Snake::Game();
	game->Initialization();

	while (window->isOpen())
	{
		game->HandleWindowEvents(*window, *event);

		if (!window->isOpen())
		{
			break;
		}

		game->Update(*window);

		window->clear();
		game->Draw(*window);
		window->display();
	}

	delete event;
	delete window;
	delete videoMode;
	delete game;

	return 0;
}