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
	toolHeaderText.setFont(this->font);
	toolHeaderText.setString("TOOLS");
	toolHeaderText.setCharacterSize(20);
	toolHeaderText.setFillColor(sf::Color::White);
	if (selectToolTex.loadFromFile("../Textures/SelectToolIcon.png"))
	{
		std::cout << "Error loading texture";
	}
	if (painToolTex.loadFromFile("../Textures/PaintToolIcon.png"))
	{
		std::cout << "Error loading texture";
	}

	this->map = map;
	this->gridSelectionRect.setFillColor(sf::Color(255,255,255,100));
	this->gridSelectionRect.setOutlineColor(sf::Color::Green);
	this->gridSelectionRect.setSize(this->map->GetGridSizeF() * sf::Vector2f(1.f, 1.f));
	this->gridSelectionRect.setOutlineThickness(1.f);
	this->currentSelectedTool = ToolType::PAINT;
	this->toolHeaderText.setPosition(1560, 905);
	this->toolHeaderText.setStyle(sf::Text::Bold);
	this->toolButtons["Paint"] = new GUI::Button(sf::Vector2f(1510, 930), sf::Vector2f(50, 50), &this->font, "", sf::Color::White, sf::Color::Cyan, sf::Color::Red,0,&painToolTex);
	this->toolButtons["Select"] = new GUI::Button(sf::Vector2f(1630, 930), sf::Vector2f(50, 50), &this->font, "", sf::Color::White, sf::Color::Cyan, sf::Color::Red,0,&selectToolTex);
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
	target->draw(this->toolHeaderText);

}

sf::Vector2u TileEditorTools::GetGridSelectedIndex()
{
	return sf::Vector2u( static_cast<int>(this->gridSelectionRect.getPosition().x / this->map->GetGridSizeF()),static_cast<int>(this->gridSelectionRect.getPosition().y / this->map->GetGridSizeF()));
}

void TileEditorTools::SetSelectorRect(sf::Texture* tex)
{
	this->gridSelectionRect.setTexture(tex);
}



void TileEditorTools::Input()
{
	

	if (this->toolButtons["Paint"]->IsPressed())
	{
		this->currentSelectedTool = ToolType::PAINT;
		this->gridSelectionRect.setOutlineColor(sf::Color::Red);
		this->gridSelectionRect.setFillColor(sf::Color(255, 255, 255, 100));
		this->toolButtons["Select"]->SetEnabled(true);
		this->toolButtons["Paint"]->SetEnabled(false);
		
	}
	else if (this->toolButtons["Select"]->IsPressed())
	{
		this->currentSelectedTool = ToolType::SELECT;
		this->gridSelectionRect.setOutlineColor(sf::Color::Green);
		this->gridSelectionRect.setFillColor(sf::Color::Transparent);
		this->toolButtons["Select"]->SetEnabled(false);
		this->toolButtons["Paint"]->SetEnabled(true);

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
					this->map->AddTile(tileSelectorPanel->GetSelectedTexture(), 1, tileSelectorPanel->GetTextureIndex(), sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y), false);
					prevPaintTilepos = currentTilepos;
				}
				this->layerSelector->UpdateLayerPanel(this->map->GetMap()[GetGridSelectedIndex().x][GetGridSelectedIndex().y], GetGridSelectedIndex());

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

void TileEditorTools::UpdateTags(std::vector<std::string> tags)
{
	//this->layerDropDownBox->options.resize(tags.size());
	//for (int i = 0; i < tags.size(); i++)
	//{
	//	
	//	this->layerDropDownBox->options[i]->SetButtonText(tags[i]->GetText());
	//
	//}
	//auto it = layerDropDownBox->options.begin()+tags.size();
	//layerDropDownBox->options.erase(it, layerDropDownBox->options.end());
	//this->layerDropDownBox->UpdateOptions(tags);
}


