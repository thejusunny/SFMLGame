#include "TileEditorTools.h"

TileEditorTools::TileEditorTools(TileMap *map, TileSelectorPanel *tileSelector,sf::RectangleShape* mask)
{
	this->tabSelectorMask = mask;
	this->layerSelector = tileSelector->GetLayerSelector();
	this->tileSelectorPanel = tileSelector;
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	this->map = map;
	this->gridSelectionRect.setFillColor(sf::Color::Transparent);
	this->gridSelectionRect.setOutlineColor(sf::Color::Green);
	this->gridSelectionRect.setSize(this->map->GetGridSizeF() * sf::Vector2f(1.f, 1.f));
	this->gridSelectionRect.setOutlineThickness(1.f);
	this->currentSelectedTool = ToolType::PAINT;
	this->toolButtons["paint"] = new GUI::Button(sf::Vector2f(1510, 930), sf::Vector2f(60, 35), &this->font, "PAINT", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	this->toolButtons["select"] = new GUI::Button(sf::Vector2f(1630, 930), sf::Vector2f(60, 35), &this->font, "SELECT", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	this->currentSelectedTool = ToolType::SELECT;

}

void TileEditorTools::Update()
{
	
	for (auto& button : toolButtons)
	{
		button.second->Update(InputDevices::Mouse::GetMousePosWindowf());

	}

	this->Input();
}

void TileEditorTools::Render(sf::RenderTarget* target)
{
	target->setView(*map->GetMapView());
	//if(!this->tabSelectorMask->getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
	target->draw(gridSelectionRect);
	target->setView(tileSelectorPanel->guiView);
	for (auto& btn : toolButtons)
		btn.second->Render(target);
}

sf::Vector2u TileEditorTools::GetGridSelectedIndex()
{
	return sf::Vector2u( static_cast<int>(this->gridSelectionRect.getPosition().x / this->map->GetGridSizeF()),static_cast<int>(this->gridSelectionRect.getPosition().y / this->map->GetGridSizeF()));
}

void TileEditorTools::Input()
{
	

	if (this->toolButtons["paint"]->IsPressed())
	{
		this->currentSelectedTool = ToolType::PAINT;
		this->gridSelectionRect.setOutlineColor(sf::Color::Red);
	}
	else if (this->toolButtons["select"]->IsPressed())
	{
		this->currentSelectedTool = ToolType::SELECT;
		this->gridSelectionRect.setOutlineColor(sf::Color::Green);

	}
	sf::Vector2f mouseViewPos = InputDevices::Mouse::GetMousePosView(this->map->GetMapView());
	if (!this->tabSelectorMask->getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
	{
		switch (this->currentSelectedTool)
		{
		case ToolType::PAINT:

			this->gridSelectionRect.setPosition(sf::Vector2f((int)mouseViewPos.x / (int)this->map->GetGridSizeF() * this->map->GetGridSizeF(),
				(int)mouseViewPos.y / (int)map->GetGridSizeF() * this->map->GetGridSizeF()));

				
			if (InputDevices::Mouse::GetMouseKeyPress(sf::Mouse::Left))//overwritting a tile wont be a problem since the layer is always selected 
			{
				sf::Vector2u currentTilepos = sf::Vector2u((int)mouseViewPos.x / (int)this->map->GetGridSizeF() * this->map->GetGridSizeF(),
					(int)mouseViewPos.y / (int)map->GetGridSizeF() * this->map->GetGridSizeF());
				if (currentTilepos != prevPaintTilepos)
				{
					this->map->AddTile(tileSelectorPanel->GetSelectedTexture(), tileSelectorPanel->layerDropDownbox->GetCurrentSelectedIndex() + 1, tileSelectorPanel->GetTextureIndex(), sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y), false);
					prevPaintTilepos = currentTilepos;
				}


			}
			else
				prevPaintTilepos = sf::Vector2u(-1, -1);
			
			/*if (InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Left))
				{
					std::cout << "Adding Tile" << "\n";

					this->map->AddTile(tileSelectorPanel->GetSelectedTexture(), tileSelectorPanel->layerDropDownbox->GetCurrentSelectedIndex() + 1, tileSelectorPanel->GetTextureIndex(), sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y), false);
				}
				else if (InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Right))
				{

					this->map->RemoveTile(sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y), tileSelectorPanel->layerDropDownbox->GetCurrentSelectedIndex() + 1);
				}*/
			break;
		case ToolType::SELECT:

			if (InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Button::Left))
			{

				this->gridSelectionRect.setPosition(sf::Vector2f((int)mouseViewPos.x / (int)this->map->GetGridSizeF() * this->map->GetGridSizeF(),
					(int)mouseViewPos.y / (int)map->GetGridSizeF() * this->map->GetGridSizeF()));
				this->layerSelector->UpdateLayerPanel(this->map->GetMap()[GetGridSelectedIndex().x][GetGridSelectedIndex().y], GetGridSelectedIndex());
			}

			break;

		}
	}

	
}
