#include <cassert>

#include "Mathematics.h"
#include "Text.h"
#include "TextMenu.h"

namespace Snake
{
	void TextMenu::Draw(sf::RenderWindow& window, sf::Vector2f& origin, float height)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, origin));
		hintText->setPosition(viewSize.x / 2.f, height);
		window.draw(*hintText);

		MenuItem& expandedItem = GetCurrentContext();

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem.childrens.size());
		for (auto& child : expandedItem.childrens)
		{
			if (child.isEnabled)
			{
				texts.push_back(&child.text);
			}
		}

		DrawTextList(window, texts,
			expandedItem.childrenSpacing,
			expandedItem.childrenOrientation,
			expandedItem.childrenAlignment,
			viewSize / 2.f, origin);
	}

	void TextMenu::GoBack()
	{
		MenuItem& parent = GetCurrentContext();
		if (&parent != &rootItem)
		{
			SelectMenuItem(parent);
		}
	}

	void TextMenu::HandleWindowEvents(sf::RenderWindow& window, sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::B)
			{
				GoBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				PressOnSelectedItem();
			}

			Orientation orientation = GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A)
			{
				SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
			{
				SwitchToNextMenuItem();
			}
		}
	}

	void TextMenu::Initialization(const MenuItem& item)
	{
		rootItem = item;

		InitMenuItem(rootItem);
		if (!rootItem.childrens.empty())
		{
			SelectMenuItem(rootItem.childrens.front());
		}
	}

	MenuItem& TextMenu::GetCurrentContext()
	{
		return selectedItem ? *(selectedItem->parent) : rootItem;
	}

	void TextMenu::InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.childrens)
		{
			child.parent = &item;
			InitMenuItem(child);
		}
	}

	void TextMenu::PressOnSelectedItem()
	{
		if (!selectedItem)
		{
			return;
		}

		if (selectedItem->onPressCallback)
		{
			selectedItem->onPressCallback(*selectedItem);
			return;
		}

		// default behaviour
		if (!selectedItem->childrens.empty())
		{
			SelectMenuItem(selectedItem->childrens.front());
		}
	}

	void TextMenu::SelectMenuItem(MenuItem& item)
	{
		assert(&item != &rootItem);

		if (selectedItem == &item)
		{
			return;
		}

		if (!item.isEnabled)
		{
			// Don't allow to select disabled item
			return;
		}

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->deselectedColor);
		}

		selectedItem = &item;

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->selectedColor);
		}
	}

	void TextMenu::SwitchToNextMenuItem()
	{
		if (!selectedItem)
		{
			return;
		}

		MenuItem* parent = selectedItem->parent;
		assert(parent); // There always should be parent

		auto it = std::find_if(parent->childrens.begin(), parent->childrens.end(), [this](const auto& item)
			{
				return selectedItem == &item;
			});

		it = std::next(it);
		if (it != parent->childrens.end())
		{
			SelectMenuItem(*it);
		}
	}

	void TextMenu::SwitchToPreviousMenuItem()
	{
		if (!selectedItem)
		{
			return;
		}

		MenuItem* parent = selectedItem->parent;
		assert(parent); // There always should be parent

		auto it = std::find_if(parent->childrens.begin(), parent->childrens.end(), [this](const auto& item)
			{
				return selectedItem == &item;
			});

		if (it != parent->childrens.begin())
		{
			SelectMenuItem(*std::prev(it));
		}
	}
}