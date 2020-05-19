#include "LoadSavePanel.h"

LoadSavePanel::LoadSavePanel(TileMap *map ,TileSelectorPanel *tileSelectorPanel)
{
	this->tileMap = map;
	this->isActive = true;
	this->tileSelector = tileSelectorPanel;
	this->saveTextBox = new GUI::TextBox(sf::Vector2f(1540, 650), sf::Vector2f(200, 30), sf::Color::Red, sf::Color::White, sf::Color::Black);

	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}

	tagEditor = new TagEditor(sf::Vector2f(1520, 200),sf::Vector2f(200,500),30);
	//Buttons
	buttons["Load"] = new GUI::Button(sf::Vector2f(1540, 700), sf::Vector2f(60, 35), &this->font, "Load", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Save"] = new GUI::Button(sf::Vector2f(1660, 700), sf::Vector2f(60, 35), &this->font, "Save", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
}

void LoadSavePanel::Input()
{
	if (buttons["Save"]->IsPressed())
	{
		
		tileMap->SaveToFile(saveTextBox->GetText() + ".map");

	
	
	}
	else if (buttons["Load"]->IsPressed())
	{

		
		std::string mapName = "";
		//tileSelectorGUI.saveTextBox->GetText();
		if (mapName.length() <= 1)
			tileMap->LoadFromFile("TileMap.map",tileSelector);
		else
			tileMap->LoadFromFile(mapName + ".map",tileSelector);
	
	}
}

void LoadSavePanel::ShowTab()
{
	this->isActive = true;
}

void LoadSavePanel::HideTab()
{
	this->isActive = false;
}

void LoadSavePanel::Update()
{
	if (this->isActive)
	{
		this->saveTextBox->Update();
		for (auto& btn : buttons)
			btn.second->Update(InputDevices::Mouse::GetMousePosWindowf());
	}

	this->tagEditor->Update();
	this->saveTextBox->Update();
	this->Input();
}

void LoadSavePanel::Render(sf::RenderTarget* target)
{
	if (this->isActive)
	{
		this->saveTextBox->Render(target);
		for (auto& btn : buttons)
			btn.second->Render(target);
	}
	this->tagEditor->Render(target);
	this->saveTextBox->Render(target);
}
