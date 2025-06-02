#include <map>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <vector>

#include "PopUpWindow.h"
#include "Text.h"

namespace Snake
{
	sf::Font font;
	TextMenu* popUpMenu;

	sf::Text* header;
	sf::Text* pointsReceivedByThePlayer;
	std::vector<sf::Text*> texts;

	PopUpWindow::PopUpWindow(PointsService& pointsService) : pointsService(pointsService)
	{
		popUpMenu = new TextMenu();
		header = new sf::Text();
		pointsReceivedByThePlayer = new sf::Text();
	}

	PopUpWindow::~PopUpWindow()
	{
		delete popUpMenu;
		delete header;
		delete pointsReceivedByThePlayer;

		texts.clear();
	}

	void PopUpWindow::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f* origin = new sf::Vector2f(0.5f, -2.f);

		popUpMenu->Draw(window, *origin, 150.f);

		pointsReceivedByThePlayer->setString(std::to_string(pointsService.GetPoints()));

		origin = new sf::Vector2f(0.5f, 0.f);

		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		viewSize += sf::Vector2f(0.f, -200.f);

		DrawTextList(window, texts, 16,
			Orientation::Vertical, Alignment::Middle,
			viewSize / 2.f, *origin);

		delete origin;
	}

	void PopUpWindow::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		popUpMenu->HandleWindowEvents(window, event);
	}

	void PopUpWindow::Initialization(MenuItem item, ResourceData& resourceData)
	{
		font = resourceData.font;

		SetTextData(*header, "Number of points", resourceData.font, 16);

		SetTextData(*pointsReceivedByThePlayer, "0", resourceData.font, 16);

		popUpMenu->Initialization(item);
	}

	void PopUpWindow::UpdatePop()
	{
		texts.clear();

		texts.push_back(header);
		texts.push_back(pointsReceivedByThePlayer);

		std::map<std::string, int>& map = pointsService.GetRecordsTable();

		for (std::map<std::string, int>::iterator it = map.begin(); it != map.end(); it++)
		{
			sf::Text* record = new sf::Text();

			SetTextData(*record, it->first + " - " + std::to_string(it->second), font, 16);

			texts.push_back(record);
		}
	}
}