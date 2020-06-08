#include "TileEditorTabSelector.h"


TileEditorTabSelector::TileEditorTabSelector(TileMap *map)
{

	
	this->InitFonts();
	this->currentSelectedTabKeyString = "TileSelector";
	this->sideMainPanel.setSize(sf::Vector2f(500, 1080));
	this->sideMainPanel.setPosition(sf::Vector2f(1490, 0));
	this->sideTabPanel.setSize(sf::Vector2f(60, 1080));
	this->sideTabPanel.setPosition(1850, 0);
	this->sideMainPanel.setFillColor(sf::Color(0, 0, 255, 100));
	this->sideTabPanel.setFillColor(sf::Color(0, 255, 255,150));
	// find a way to pass tilemap to load and save class without creating aditional dependencies

	this->panelHeadingText.setFont(this->font);
	this->panelHeadingText.setString("MENU");
	this->panelHeadingText.setCharacterSize(18);
	this->panelHeadingText.setFillColor(sf::Color::White);
	this->panelHeadingText.setPosition(sf::Vector2f(1858, 5));
	
	this->tabs["TileSelector"] = new Tab(new GUI::Button(sf::Vector2f(1850, 50), sf::Vector2f(60, 40), &this->font, "TileSelector", sf::Color::White, sf::Color::Cyan, sf::Color::Red,12), new TileSelectorPanel(map,&this->sideMainPanel));
	this->tabs["Tags"] = new Tab(new GUI::Button(sf::Vector2f(1850, 100), sf::Vector2f(60, 40), &this->font, "Tags", sf::Color::White, sf::Color::Cyan, sf::Color::Red, 12), new TagsPanel(GetPanel<TileSelectorPanel>("TileSelector")->GetLayerSelector()));
	this->tabs["Save&Load"] = new Tab(new GUI::Button(sf::Vector2f(1850, 150), sf::Vector2f(60, 40), &this->font, "Save&Load", sf::Color::White, sf::Color::Cyan, sf::Color::Red,12), new LoadSavePanel(map,GetPanel<TileSelectorPanel>("TileSelector")));
	this->prevButton = NULL;

}
void TileEditorTabSelector::Update()
{
	for (auto& tab : tabs)
	{
		tab.second->button->Update(InputDevices::Mouse::GetMousePosWindowf());
	}
	this->tabs[this->currentSelectedTabKeyString]->panel->Update();
	this->Input();
}

void TileEditorTabSelector::Render(sf::RenderTarget* target)
{
	target->draw(this->sideMainPanel);

	target->draw(this->sideTabPanel);
	this->tabs[this->currentSelectedTabKeyString]->panel->Render(target);
	for (auto& tab : tabs)
	{
		tab.second->button->Render(target);
	}
	target->draw(this->panelHeadingText);
	
}

const bool TileEditorTabSelector::IsMouseEnteringPanel() const
{

	return (this->sideMainPanel.getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()));
}


void TileEditorTabSelector::Input()
{
	
	for (auto &tab : tabs)
	{

		if (tab.second->button->IsPressed())
		{
			if (prevButton != NULL)
				prevButton->SetEnabled(true);
			tab.second->button->SetEnabled(false);
			tabs[this->currentSelectedTabKeyString]->panel->HideTab();
			this->currentSelectedTabKeyString = tab.first;
			tab.second->panel->ShowTab();
			prevButton = tab.second->button;
		
		}
	}
	
	
}

void TileEditorTabSelector::InitFonts()
{
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
}
