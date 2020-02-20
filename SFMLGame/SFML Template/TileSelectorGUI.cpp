#include "TileSelectorGUI.h"

void TileSelectorGUI::Update()
{
	sf::Vector2f relativePosition;

	//relativePosition.x = static_cast<int>((Mouse::GetMousePosWindowi().x - tileSelectorPanelPosition.x))/static_cast<int>(selectionTileSize.x+20)*(selectionTileSize.x+10)+ tileSelectorPanelPosition.x;
	//relativePosition.y = static_cast<int>((Mouse::GetMousePosWindowi().y - tileSelectorPanelPosition.y))/ static_cast<int>(selectionTileSize.y+20) * (selectionTileSize.y+10)+ tileSelectorPanelPosition.y;
	/*this->tileSelectorRect.setPosition(Mouse::GetMousePosWindowf());*/
	
	this->Input();
}



TileSelectorGUI::TileSelectorGUI()
{
	textures.resize(50);
	this->selectedTileIndex = 0;
	this->selectionTileSize = sf::Vector2f(50, 50);
	for (size_t i = 0; i < 50; i++)
	{
		std::string tileName;
		if(i<=9)
			tileName ="../Tiles/tile_000"+ std::to_string(i)+".png";
		else
			tileName = "../Tiles/tile_00" + std::to_string(i) + ".png";
		
		if (!textures[i].loadFromFile(tileName))
		{
			std::cout << "Couldnt load textures into tile selctor";
			exit(0);
		}
	}
	this->tilePadding = 20.f;
	this->tileSelectorRect.setFillColor(sf::Color::Transparent);
	this->tileSelectorRect.setOutlineColor(sf::Color::Red);
	this->tileSelectorRect.setOutlineThickness(1.f);
	this->tileSelectorRect.setSize(sf::Vector2f( this->selectionTileSize.x+20,this->selectionTileSize.y+this->tilePadding));
	this->availableTiles.resize(50);
	this->tileSelectorPanel.setFillColor(sf::Color(255, 255, 255, 50));
	this->tileSelectorPanelSize = sf::Vector2f(350, 430);
	this->tileSelectorPanel.setSize(this->tileSelectorPanelSize);
	this->tileSelectorPanelPosition = sf::Vector2f(1500, 100);
	this->tileSelectorPanel.setPosition(this->tileSelectorPanelPosition);

	int row = 0;
	float newPositionX;
	this->noOfCollums = (this->tileSelectorPanelSize.x / selectionTileSize.x) - 1;
	this->noOfRows = this->availableTiles.size() / noOfCollums;


	for (size_t y = 0; y < noOfRows; y++)
	{
		for (size_t x = 0; x < noOfCollums; x++)
		{
			newPositionX = this->tileSelectorPanelPosition.x + 10 + x * (this->selectionTileSize.x + this->tilePadding);
			
				
			availableTiles[x+y* (this->noOfCollums)].setSize(sf::Vector2f(50.f, 50.f));
			availableTiles[x + y * (this->noOfCollums)].setPosition(sf::Vector2f(newPositionX,
				this->tileSelectorPanelPosition.y+10 +y*(this->selectionTileSize.y+this->tilePadding) ));

			availableTiles[(x + y * (this->noOfCollums))].setTexture(&textures[x+y* (this->noOfCollums)]);
		
			
		}
	}
}
void TileSelectorGUI::Render(sf::RenderTarget* target)
{
	target->draw(this->tileSelectorPanel);
	for (auto& tile : availableTiles)
	{
		if (this->tileSelectorPanel.getGlobalBounds().contains(tile.getPosition()))
			target->draw(tile);
	}
	//if (this->tileSelectorPanel.getGlobalBounds().contains(Mouse::GetMousePosWindowf()))
	target->draw(this->tileSelectorRect);
}
const sf::RectangleShape TileSelectorGUI::GetSelectorPanel() const
{
	return this->tileSelectorPanel;
}

void TileSelectorGUI::Input()
{
	sf::Vector2f relativePosition;
	sf::Vector2i selectedTileIndex2D;
	if (this->tileSelectorPanel.getGlobalBounds().contains(Mouse::GetMousePosWindowf()))
	{
	
		if (Mouse::GetMouseKeyDown(sf::Mouse::Left))
		{
		
			selectedTileIndex2D.x = (static_cast<int>((Mouse::GetMousePosWindowf().x - tileSelectorPanelPosition.x)) / static_cast<int>((selectionTileSize.x + this->tilePadding)));
			selectedTileIndex2D.y = (static_cast<int>((Mouse::GetMousePosWindowf().y - tileSelectorPanelPosition.y)) / static_cast<int>((selectionTileSize.y + this->tilePadding)));
			relativePosition.x = ((selectedTileIndex2D.x) * (selectionTileSize.x + this->tilePadding))+ tileSelectorPanelPosition.x;
			relativePosition.y = ((selectedTileIndex2D.y)* (selectionTileSize.x + this->tilePadding))+ tileSelectorPanelPosition.y;
			this->selectedTileIndex = ((selectedTileIndex2D.y * this->noOfCollums) + selectedTileIndex2D.x);
			std::cout << this->selectedTileIndex;
			this->tileSelectorRect.setPosition(relativePosition);
	
		}
	}
	
}

const bool TileSelectorGUI::IsActive() const
{
	return this->isActive;
}

sf::Texture* TileSelectorGUI::GetSelectedTexture()
{
	
	return &textures[this->selectedTileIndex];
}


