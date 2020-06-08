#include "TileLayerSelector.h"



TileLayerSelector::TileLayerSelector(TileMap *map)
{
	this->noOfLayers = 4;
	this->layers.resize(this->noOfLayers);
	this->tileIcons.resize(this->noOfLayers);
	this->map = map;
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	this->mainPanel.setSize(sf::Vector2f( 200, 300));
	this->mainPanel.setPosition(sf::Vector2f(1510, 600));
	float baseTileSize = mainPanel.getSize().y / noOfLayers;
	for (int i = 0; i < noOfLayers; i++)
	{
		this->layers[i] = new Layer(i,mainPanel.getPosition()+sf::Vector2f(baseTileSize, i*baseTileSize),sf::Vector2f(mainPanel.getSize().x-baseTileSize,baseTileSize),this->font);
		this->tileIcons[i].setSize(sf::Vector2f(baseTileSize, baseTileSize));
		this->tileIcons[i].setPosition(mainPanel.getPosition()+sf::Vector2f(0,i*baseTileSize));
		this->tileIcons[i].setOutlineColor(sf::Color::Black);
		this->tileIcons[i].setOutlineThickness(1.f);
		this->tileIcons[i].setFillColor(sf::Color(255, 255, 255, 150));
	
	}
	this->layerDropDownBox = new GUI::DropDownBox(std::vector<std::string>{"Layer1", "Layer2", "Thej", "The", "Thejus", "Th", "Thejussss", "Thmore", "Layer6"}, sf::Vector2f(100, 30), sf::Vector2f(1740, 600), true);
	

	this->selectedRect.setOutlineColor(sf::Color::White);
	this->selectedRect.setOutlineThickness(1.f);
	this->selectedRect.setSize(sf::Vector2f(baseTileSize, baseTileSize));
	this->selectedRect.setFillColor(sf::Color(255,255,255,200));
	//<Mock>
	/*std::vector<Tile*> t  = this->map->GetMap()[1][2];
	
	for (int i=0;i<t.size();i++)
	{
		if (t[i] != NULL)
		{
			tileIcons[i].setTexture(t[i]->GetTexture());
		}
	}*/
	this->selectedIconIndex = -1;
	this->selectedOutlineThickness = 2.f;
	this->selectedOutlineColor = sf::Color::Red;
	
}
void TileLayerSelector::UpdateLayerIcons()
{
	for (int i = tileBuffer.size()-1; i >=0; i--)
	{
		tileIcons[i].setTexture(NULL);
		if (tileBuffer[i] != NULL)
		{
			this->tileIcons[i].setFillColor(sf::Color(255, 255, 255));
			tileIcons[i].setTexture(tileBuffer[i]->GetTexture());

		}
	}
}
void TileLayerSelector::UpdateSelectedTile(int index)
{
	
	if (index < 0)
	{

		if (selectedIconIndex >= 0)
		{
			this->tileIcons[selectedIconIndex].setOutlineColor(sf::Color::Black);
			this->tileIcons[selectedIconIndex].setOutlineThickness(1.f);
			this->layerDropDownBox->SetCurrentSelectedString("");
		}
		selectedIconIndex = index;
		return;
	}
		

	if (selectedIconIndex >= 0)
	{
		this->tileIcons[selectedIconIndex].setOutlineColor(sf::Color::Black);
		this->tileIcons[selectedIconIndex].setOutlineThickness(1.f);

	}


	this->selectedIconIndex = index;

	this->layerDropDownBox->SetCurrentSelectedString(this->tileBuffer[index]->GetTileTag());
	this->tileIcons[selectedIconIndex].setOutlineColor(sf::Color::Red);
	this->tileIcons[selectedIconIndex].setOutlineThickness(selectedOutlineThickness);
}

void TileLayerSelector::UpdateLayerPanel(std::vector<Tile*> tiles,sf::Vector2u tileIndex)
{
	this->tileBuffer = tiles;
	this->tileIndex = tileIndex; // global tile position
	UpdateSelectedTile(-1);
	this->UpdateLayerIcons();
	

}
void Layer::Render(sf::RenderTarget* target)
{
	target->draw(layerRects);
	//target->draw(tileType);
	target->draw(layerName);
	
}
void TileLayerSelector::Update()
{
	
	this->layerDropDownBox->Update();
	
	
	this->Input();

}
void TileLayerSelector::Render(sf::RenderTarget* target)
{
	target->draw(this->mainPanel);
	for (auto& i : layers)
		i->Render(target);
	for (int i=0;i<tileIcons.size();i++)
	{

		target->draw(tileIcons[i]);
	}

	if(iconHeld)
	target->draw(this->selectedRect);
	this->layerDropDownBox->Render(target);


}
void TileLayerSelector::UpdateTags(std::vector<std::string> tags)
{
	//this->layerDropDownBox->options.resize(tags.size());
	//for (int i = 0; i < tags.size(); i++)
	//{
	//	
	//	this->layerDropDownBox->options[i]->SetButtonText(tags[i]);
	//
	//}
	//auto it = layerDropDownBox->options.begin()+tags.size();
	//layerDropDownBox->options.erase(it, layerDropDownBox->options.end());
	this->layerDropDownBox->UpdateOptions(tags);
}
void TileLayerSelector::Input()
{
	
	if (this->layerDropDownBox->IsChanged())
	{
	
		this->tileBuffer[selectedIconIndex]->SetTileTag(this->layerDropDownBox->GetCurrentSelectedString());
		this->map->UpdateLayers(tileIndex, tileBuffer);
	
	}
	
	//if mouse inside the whole panel do this
	for (int i=0;i<this->noOfLayers;i++)
	{
		
		if(InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Button::Left))
		{
			if (tileIcons[i].getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()) && tileIcons[i].getTexture() != NULL)
			{
				

				this->iconSeleceted = true;
				this->UpdateSelectedTile(i);
			}
			
		
		}
		
		if (InputDevices::Mouse::GetMouseKeyPress(sf::Mouse::Button::Left))
		{
			if (!iconHeld)
			{
				if (tileIcons[i].getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf())&&tileIcons[i].getTexture()!=NULL)
				{

					this->iconHeld = true;
					this->mouseHeldIndex = i;
					this->selectedRect.setTexture(tileBuffer[mouseHeldIndex]->GetTexture());



				}
			}
			else
				this->selectedRect.setPosition(InputDevices::Mouse::GetMousePosWindowf());
			
		}
		else
		{
			if (iconHeld)
			{
				if (tileIcons[i].getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
				{
				
					
						Tile* tileToMove = tileBuffer[mouseHeldIndex];

						bool isLayerBoxFull = true;
						for (auto* i : tileBuffer)
						{
							if (i == NULL)
								isLayerBoxFull = false;
						}
						
						if (tileBuffer[i] == NULL)
						{
							tileBuffer[mouseHeldIndex] = NULL;
							tileBuffer[i] = tileToMove;
						}
						else
						{
							tileBuffer[mouseHeldIndex] = tileBuffer[i];
							tileBuffer[i] = tileToMove;
						}
							
					


						this->UpdateLayerIcons();
						selectedRect.setTexture(NULL);
						this->map->UpdateLayers(tileIndex, tileBuffer);
						std::cout << "Dropped at " + i << "Selected Index " + mouseHeldIndex;
						if (iconSeleceted)
						{
							this->UpdateSelectedTile(i);
						}
						iconHeld = false;
						mouseHeldIndex = -1;
					}
					
				}
				
			
		}

		
	}
}

Layer::Layer(int layerIndex, sf::Vector2f layerRectPos,sf::Vector2f layerRectSize,sf::Font &font)
{
	

	this->layerRects.setPosition(layerRectPos);
	
	this->layerRects.setSize(layerRectSize);
	this->layerRects.setOutlineColor(sf::Color::Black);
	this->layerRects.setOutlineThickness(1.f);

	this->layerRects.setFillColor(sf::Color(200, 0, 0, 150));
	this->tileType.setFont(font);


	this->layerName.setCharacterSize(20);
	this->layerName.setPosition(sf::Vector2f(4,4)+ layerRectPos);
	this->layerName.setFont(font);
	this->layerName.setFillColor(sf::Color::White);
	this->layerName.setFont(font);
	this->layerName.setString("Layer " + std::to_string(layerIndex+1));// std::stoi to str->int
	this->tileType.setString("None");
	
	
}

