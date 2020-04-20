#include "TileSelectorPanel.h"


TileSelectorPanel::TileSelectorPanel(TileMap *map,  sf::RectangleShape* tabSelectorMask)
{

	this->maxTiles = 480;
	this->tilePadding = 20.f;
	this->currentPageIndex = 0;
	this->selectedTileIndex = 0;

	this->guiView.setSize(sf::Vector2f(1920, 1080));
	this->guiView.setCenter(sf::Vector2f(1920 / 2, 1080 / 2));

	this->InitFonts();
	this->LoadTileGUITextures();

	//Panel iniitilization 
	this->InitTileSelectionPanel();

	this->noOfCollums = (this->tileSelectorPanelSize.x / (tileSize.x + this->tilePadding));
	this->noOfRows = (this->tileSelectorPanelSize.y / (tileSize.y + this->tilePadding));

	

	this->noOfPages = this->textures.size() / (this->noOfRows * this->noOfCollums);
	
	this->MapTexturesToTileSelectorGUI();

	this->InitNavigationPanel();
	
	this->layerSelector = new TileLayerSelector(map);
	this->tileEditorTools = new TileEditorTools(map,this,tabSelectorMask);
	this->layerDropDownbox = new GUI::DropDownBox(std::vector<std::string>{"Layer1", "Layer2", "Layer3", "Layer4"}, sf::Vector2f(100, 30), sf::Vector2f(1540, 750));

}
TileSelectorPanel::~TileSelectorPanel()
{

	for (auto& it : buttons)
		delete& it;
	
}
void TileSelectorPanel::InitFonts()
{
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}

}
void TileSelectorPanel::LoadTileGUITextures()
{
	textures.resize(this->maxTiles);
	for (size_t i = 0; i < this->maxTiles; i++)
	{
		std::string tileName;
		if (i <= 9)
			tileName = "../Tiles/tile_000" + std::to_string(i) + ".png";
		else if (i <= 99)
			tileName = "../Tiles/tile_00" + std::to_string(i) + ".png";
		else
			tileName = "../Tiles/tile_0" + std::to_string(i) + ".png";

		if (!textures[i].loadFromFile(tileName))
		{
			std::cout << "Couldnt load textures into tile selctor";
			exit(0);
		}
	}
}
void TileSelectorPanel::MapTexturesToTileSelectorGUI()
{
	float newPositionX;
	this->availableTiles.resize(this->noOfPages);
	for (size_t pageNo = 0; pageNo < this->noOfPages; pageNo++)
	{
		this->availableTiles[pageNo].resize(this->noOfRows * this->noOfCollums);
		for (size_t y = 0; y < noOfRows; y++)
		{
			for (size_t x = 0; x < noOfCollums; x++)
			{
				newPositionX = this->tileSelectorPanelPosition.x + 10 + x * (this->tileSize.x + this->tilePadding);// 10 is the initial padding
				availableTiles[pageNo][x + y * (this->noOfCollums)].setSize(this->tileSize);
				availableTiles[pageNo][x + y * (this->noOfCollums)].setPosition(sf::Vector2f(newPositionX,
					this->tileSelectorPanelPosition.y + 10 + y * (this->tileSize.y + this->tilePadding)));// 10 for initial padding

				availableTiles[pageNo][(x + y * (this->noOfCollums))].setTexture(&textures[x + y * (this->noOfCollums) + ((this->noOfCollums * this->noOfRows * pageNo))]);

			}
		}
	}
}
void TileSelectorPanel::InitNavigationPanel()
{

	//Panel
	this->tileSelectorNavigationPanel.setPosition(this->tileSelectorPanelPosition.x, this->tileSelectorPanelPosition.y + this->tileSelectorPanelSize.y);
	this->tileSelectorNavigationPanel.setSize(sf::Vector2f(this->tileSelectorPanelSize.x, 100));
	this->tileSelectorNavigationPanel.setFillColor(sf::Color(50, 50, 50, 100));
	this->tileSelectorNavigationPanel.setOutlineColor(sf::Color(255, 0, 0, 255));
	this->tileSelectorNavigationPanel.setOutlineThickness(1.f);

	//Buttons
	buttons["Prev_Page_Button"] = new GUI::Button(sf::Vector2f(1600, 510), sf::Vector2f(60, 35), &this->font, "Prev", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Next_Page_Button"] = new GUI::Button(sf::Vector2f(1750, 510), sf::Vector2f(60, 35), &this->font, "Next", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	
	
	//PageText
	pageNoText.setFont(this->font);
	pageNoText.setFillColor(sf::Color::White);
	pageNoText.setCharacterSize(15);
	pageNoText.setPosition(sf::Vector2f(1695, 520));
	pageNoText.setString(std::to_string((this->currentPageIndex + 1)) + "/" + std::to_string(this->noOfPages));
}
void TileSelectorPanel::InitTileSelectionPanel()
{
	
	this->tileSize = sf::Vector2f(50, 50);
	this->selectionHeaderText.setFont(this->font);
	this->selectionHeaderText.setFillColor(sf::Color::White);
	this->selectionHeaderText.setString("Tile Selectoion panel");
	//Tileselectorpanel
	this->tileSelectorPanel.setFillColor(sf::Color(50, 50, 50, 100));
	this->tileSelectorPanel.setOutlineColor(sf::Color(255, 255, 255, 200));
	this->tileSelectorPanel.setOutlineThickness(1.f);
	this->tileSelectorPanelSize = sf::Vector2f(350, 420);
	this->tileSelectorPanel.setSize(this->tileSelectorPanelSize);
	this->tileSelectorPanelPosition = sf::Vector2f(1500, 60);
	this->tileSelectorPanel.setPosition(this->tileSelectorPanelPosition);


	//TileSelectorRect
	this->tileSelectorRect.setPosition(this->tileSelectorPanel.getPosition());
	
	this->tileSelectorRect.setFillColor(sf::Color(255,0,0,50));
	this->tileSelectorRect.setOutlineColor(sf::Color::White);
	this->tileSelectorRect.setOutlineThickness(1.f);
	this->tileSelectorRect.setSize(sf::Vector2f(this->tileSize.x + 20, this->tileSize.y + this->tilePadding));

}

int TileSelectorPanel::GetTextureIndex()
{
	return this->selectedTileIndex + (this->noOfCollums * this->noOfRows) * this->currentPageIndex;
}
void TileSelectorPanel::Update()
{
	sf::Vector2f relativePosition;
	for (auto& button : buttons)
	{
		button.second->Update(InputDevices::Mouse::GetMousePosView(&this->guiView));
	

	}
	layerSelector->Update();
	tileEditorTools->Update();
	/*this->saveTextBox->Update();
	this->layerDropDownbox->Update();*/
	this->Input();
	pageNoText.setString(std::to_string((this->currentPageIndex + 1)) + "/" + std::to_string(this->noOfPages));
}
void TileSelectorPanel::Render(sf::RenderTarget* target)
{
	target->setView(this->guiView);
	target->draw(this->tileSelectorPanel);
	for (auto& tile : availableTiles[this->currentPageIndex])
	{
		if (this->tileSelectorPanel.getGlobalBounds().contains(tile.getPosition()))
			target->draw(tile);
	}
	target->draw(tileSelectorNavigationPanel);
	for (auto& button : buttons)
		button.second->Render(target); 
	this->layerSelector->Render(target);
	this->tileEditorTools->Render(target);
	/*this->saveTextBox->Render(target);
	this->layerDropDownbox->Render(target);*/
	

	target->draw(this->pageNoText);
	//if (this->tileSelectorPanel.getGlobalBounds().contains(Mouse::GetMousePosWindowf()))
	target->draw(this->tileSelectorRect);

}
void TileSelectorPanel::Input()
{
	sf::Vector2f relativePosition;
	sf::Vector2i selectedTileIndex2D;
	if (this->tileSelectorPanel.getGlobalBounds().contains(InputDevices::Mouse::GetMousePosView(&this->guiView)))
	{

		if (InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Left))
		{

			std::cout << tileSelectorPanelPosition.x << ","<< InputDevices::Mouse::GetMousePosWindowf().x<<std::endl;
			selectedTileIndex2D.x = (static_cast<int>((InputDevices::Mouse::GetMousePosWindowf().x - tileSelectorPanelPosition.x)) / static_cast<int>((tileSize.x + this->tilePadding)));
			selectedTileIndex2D.y = (static_cast<int>((InputDevices::Mouse::GetMousePosWindowf().y - tileSelectorPanelPosition.y)) / static_cast<int>((tileSize.y + this->tilePadding)));
			relativePosition.x = ((selectedTileIndex2D.x) * (tileSize.x + this->tilePadding)) + tileSelectorPanelPosition.x;
			relativePosition.y = ((selectedTileIndex2D.y) * (tileSize.x + this->tilePadding)) + tileSelectorPanelPosition.y;
			this->selectedTileIndex = ((selectedTileIndex2D.y * this->noOfCollums) + selectedTileIndex2D.x);
			//std::cout << this->selectedTileIndex;
			this->tileSelectorRect.setPosition(relativePosition);

		}
	}
	if (this->currentPageIndex < this->noOfPages - 1 && this->buttons["Next_Page_Button"]->IsPressed())
		++this->currentPageIndex;
	else if (this->currentPageIndex > 0 && this->buttons["Prev_Page_Button"]->IsPressed())
		--this->currentPageIndex;
	
}

const sf::RectangleShape TileSelectorPanel::GetSelectorPanel() const
{
	return this->tileSelectorPanel;
}


const bool TileSelectorPanel::IsActive() const
{
	return this->isActive;
}

sf::Texture* TileSelectorPanel::GetSelectedTexture()
{
	
	//std::cout << this->selectedTileIndex;
	return &this->textures[this->selectedTileIndex+(this->noOfCollums*this->noOfRows)*this->currentPageIndex];
}

sf::Texture* TileSelectorPanel::GetTextureFromIndex(int index)
{
	if(index<textures.size()-1)
	return &this->textures[index];
	return NULL;
}



bool TileSelectorPanel::IsMouseEnteringPanel()
{
	if (this->tileSelectorPanel.getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()) || this->tileSelectorNavigationPanel.getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
		return true;

	return false;
}

void TileSelectorPanel::SetActive(bool state)
{
	this->isActive = state;
}
void TileSelectorPanel::HideTab()
{
	this->isActive = false;
}

TileLayerSelector* TileSelectorPanel::GetLayerSelector() const
{
	return this->layerSelector;
}

void TileSelectorPanel::ShowTab()
{
	this->isActive = true;
}






