#include "TileMap.h"
#include<iostream>
TileMap::TileMap( float gridSize, sf::Vector2u maxSize, unsigned int layers)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(gridSizeF);
	this->layers = layers;
	this->maxSize = maxSize;
	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.push_back(std::vector< std::vector<Tile*>>());
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y);
			this->map[x].push_back( std::vector<Tile*>()); // 2nd vector
			for (size_t z = 0; z < layers; z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(NULL); // 3rd vector

			}
		}
	}
}

TileMap::~TileMap()
{ 
	for (size_t x = 0; x < maxSize.x; x++)
	{
		for (size_t y = 0;  y < maxSize.y;  y++)
		{
			for (size_t z= 0;  z < layers;  z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

void TileMap::Render(sf::RenderTarget &target)
{

	for (auto& x: this->map)
	{
	
		for (auto& y : x)
		{
			for (auto *z : y)
			{
				if(z !=nullptr)// if the tile is not deleted or empty
				z->Render(target);
			}
		}
	}
	
}

void TileMap::RemoveTile(sf::Vector2u position)
{
	sf::Vector2u gridPosition;
	gridPosition.x = position.x / gridSizeU;
	gridPosition.y = position.y / gridSizeU;
	//std::cout << "Removing Tile";
	if (this->map[gridPosition.x][gridPosition.y][layers] != nullptr)
	{
		delete this->map[gridPosition.x][gridPosition.y][layers];
		this->map[gridPosition.x][gridPosition.y][layers] = nullptr;
	}
}

void TileMap::AddTile( sf::Texture* texture, sf::Vector2u position)
{
	sf::Vector2u gridPosition;

	gridPosition.x = position.x / gridSizeU;
	gridPosition.y = position.y / gridSizeU;
	
	if (this->map[gridPosition.x][gridPosition.y][layers] != nullptr)
	{
		this->map[gridPosition.x][gridPosition.y][layers]->SetTexture(texture);
	
	}
	else
	{
		this->map[gridPosition.x][gridPosition.y][layers] = new Tile(texture,position,80);
		
		

	}
		

}
