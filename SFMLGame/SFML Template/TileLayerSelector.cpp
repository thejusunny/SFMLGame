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
void TileLayerSelector::UpdateLayerPanel(std::vector<Tile*> tiles,sf::Vector2u tileIndex)
{
	this->tileBuffer = tiles;
	this->tileIndex = tileIndex;
	this->UpdateLayerIcons();
	

}
void Layer::Render(sf::RenderTarget* target)
{
	target->draw(layerRects);
	target->draw(tileType);
	target->draw(layerName);
}
void TileLayerSelector::Update()
{
	this->Input();
}
void TileLayerSelector::Render(sf::RenderTarget* target)
{
	target->draw(this->mainPanel);
	for (int i=0;i<tileIcons.size();i++)
	{

		target->draw(tileIcons[i]);
	}
	for (auto& i : layers)
		i->Render(target);
	if(iconSelected)
	target->draw(this->selectedRect);
}
void TileLayerSelector::Input()
{
	//if mouse inside the whole panel do this
	for (int i=0;i<this->noOfLayers;i++)
	{
		if (InputDevices::Mouse::GetMouseKeyPress(sf::Mouse::Button::Left))
		{
			if (!iconSelected)
			{
				if (tileIcons[i].getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
				{

					this->iconSelected = true;
					this->mouseHeldIndex = i;
					this->selectedRect.setTexture(tileBuffer[mouseHeldIndex]->GetTexture());



				}
			}
			else
				this->selectedRect.setPosition(InputDevices::Mouse::GetMousePosWindowf());
			
		}
		else
		{
			if (iconSelected)
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
							
					


						//if (isLayerBoxFull)// If layer box is full swap the icons
						//{
						//	tileBuffer[mouseHeldIndex] = tileBuffer[i];
						//	tileBuffer[i] = tileToMove;


						//}
						//else// move it up and down
						//{
						//	
						//		
						//		if (tileBuffer[i] != NULL)// if target tile is not empty then move it 
						//		{
						//			int indexToDelete = -1;
						//			for (int x = i; x < tileBuffer.size();x++)// find the closest empty slot and delete it
						//			{
						//				if (tileBuffer[x] == NULL)
						//					indexToDelete = x;
						//			
						//			}
						//			if (indexToDelete > 0)
						//			{
						//				tileBuffer[mouseHeldIndex] = NULL;
						//				tileBuffer.erase(tileBuffer.begin() + indexToDelete);
						//				tileBuffer.insert(tileBuffer.begin() + i, tileToMove);
						//			}
						//			//else
						//			//tileBuffer.insert(tileBuffer.begin() + i, tileToMove);
						//			////tileBuffer.erase(tileBuffer.begin() + mouseHeldIndex);
						//			//tileBuffer.erase(tileBuffer.begin() + tileIcons.size());
						//		}
						//		else
						//		{// replace the empty tile 
						//			tileBuffer[mouseHeldIndex] = NULL;
						//			tileBuffer[i] = tileToMove;
						//		}
						//
						//}
						//for (int i = 0; i < tileBuffer.size(); i++)
						//{
						//	tileIcons[i].setTexture(NULL);
						//	if (tileBuffer[i] != NULL)
						//	{
						//		this->tileIcons[i].setFillColor(sf::Color(255, 255, 255));
						//		tileIcons[i].setTexture(tileBuffer[i]->GetTexture());

						//	}
						//}
						this->UpdateLayerIcons();
						selectedRect.setTexture(NULL);
						this->map->UpdateLayers(tileIndex, tileBuffer);
						std::cout << "Dropped at " + i << "Selected Index " + mouseHeldIndex;
						iconSelected = false;
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
	this->layerRects.setOutlineColor(sf::Color::Green);
	this->layerRects.setOutlineThickness(1.f);

	this->layerRects.setFillColor(sf::Color(200, 0, 0, 150));
	this->tileType.setFont(font);
	this->layerName.setFont(font);
	this->layerName.setString("Layer " + (layerIndex+1));
	this->tileType.setString("None");
	
	
}

