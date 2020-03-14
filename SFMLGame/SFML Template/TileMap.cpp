#include "TileMap.h"
#include<iostream>
TileMap::TileMap( float gridSize, sf::Vector2u maxSize, unsigned int layers,TileSelectorGUI *gui,sf::RectangleShape *mask,sf::View *view)
{
	this->gridSizeF = gridSize;
	this->tileSelectionGUI = gui;
	this->rectMask = mask;
	this->view = view;
	this->gridSizeU = static_cast<unsigned>(gridSizeF);
	if (layers <= 0)
		layers = 1;
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
	this->collisionRect.setFillColor(sf::Color(255, 0, 0, 100));
	this->collisionRect.setSize(sf::Vector2f( gridSizeF,gridSizeF));
	this->collisionRect.setOutlineColor(sf::Color(0, 255, 0, 255));
	this->collisionRect.setOutlineThickness(1.f);

}
void TileMap::SaveToFile(std::string fileName)
{
	std::ofstream outFile;

	std::string filePath = "../"+fileName;
	outFile.open(filePath);

	/*
	MAXSIZE X,Y- Size of the whole TileMap X x Y
	GRIDSIZE - Size of Each Tile
	LAYERS 
	
	X Y Z positions, TextureIndex, Collision

	*/

	if (outFile.is_open())
	{

		outFile << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n" << this->layers<< "\n";


		for (size_t x = 0; x < maxSize.x; x++)
		{
			for (size_t y = 0; y < maxSize.y; y++)
			{
				for (size_t z = 0; z < layers; z++)
				{
				
					if (this->map[x][y][z])
					{
						outFile << x << " " << y << " " << z << " " << this->map[x][y][z]->GetTileInfoAsString()<<"	";
						std::cout << "Addding info into file \n";
					}
					
				}
			}
		}
	}
	
	outFile.close();


}

void TileMap::LoadFromFile(std::string fileName)
{
	/*
	MAXSIZE X,Y- Size of the whole TileMap X x Y
	GRIDSIZE - Size of Each Tile
	LAYERS

	X Y Z positions, TextureIndex, Collision

	*/
	this->ClearMap();
	this->gridSizeU = static_cast<unsigned>(gridSizeF);
	this->layers = layers;
	this->maxSize = maxSize;
	this->map.resize(this->maxSize.x);
	
	std::ifstream inputStream;
	std::string filePath = "../" + fileName;
	inputStream.open(filePath);
	unsigned x=0, y=0, z=0; 

	int textureIndex=0;
	bool collision;

	


	if (inputStream.is_open())
	{
		inputStream >> this->maxSize.x >> this->maxSize.y >> this->gridSizeU >> this->layers;
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			this->map.push_back(std::vector< std::vector<Tile*>>());
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y);
				this->map[x].push_back(std::vector<Tile*>()); // 2nd vector
				for (size_t z = 0; z < layers; z++)
				{
					this->map[x][y].resize(this->layers);
					this->map[x][y].push_back(NULL); // 3rd vector

				}
			}
		}
	
		std::string texturePath = "";
		while (inputStream>>x>>y>>z>> textureIndex >>collision)
		{
		
			std::cout << x<<" "<<y<<" "<<z<<" "<< textureIndex <<"\n";
			
			this->map[x][y][z] = new Tile(tileSelectionGUI->GetTextureFromIndex(textureIndex), sf::Vector2u(x*gridSizeU,y*gridSizeU), gridSizeU, textureIndex,collision);
			if(collision)
			this->collisionRect.setPosition(map[x][y][z]->GetPosition());
		}



	}
	inputStream.close();
}

void TileMap::ClearMap()
{

	for (size_t x = 0; x < maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
				if (this->map[x][y][z] != NULL)
				{
					delete this->map[x][y][z];
					this->map[x][y][z] = NULL;
				}
			}
		}
	}

}

void TileMap::Update()
{

}

TileMap::~TileMap()
{ 
	for (size_t x = 0; x < maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
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
				if(z !=nullptr )// if the tile is not deleted or empty
				{ 
					
					z->Render(target);
					if (z->IsCollidable())
					{
						this->collisionRect.setPosition(z->GetPosition());
						target.draw(this->collisionRect);
					}
					
					
				
				}
				
			
			}
		}
	}
	
	
}

void TileMap::RemoveTile(sf::Vector2u position)
{
	sf::Vector2u gridPosition;
	gridPosition.x = position.x / gridSizeU;
	gridPosition.y = position.y / gridSizeU;
	std::cout << "Removing Tile";
	if (this->map[gridPosition.x][gridPosition.y][layers-1] != NULL)
	{
		delete this->map[gridPosition.x][gridPosition.y][layers-1];
		this->map[gridPosition.x][gridPosition.y][layers-1] = NULL;
	}
}

void TileMap::AddTile( sf::Texture* texture,int tileIndex, sf::Vector2u position, bool collision)
{
	sf::Vector2u gridPosition;

	gridPosition.x = position.x / gridSizeU;
	gridPosition.y = position.y / gridSizeU;
	
	if (this->map[gridPosition.x][gridPosition.y][layers-1] != NULL)
	{
		this->map[gridPosition.x][gridPosition.y][layers-1]->SetTexture(texture);
		this->map[gridPosition.x][gridPosition.y][layers - 1]->SetCollision(collision);
	
	
	}
	else
	{
		this->map[gridPosition.x][gridPosition.y][layers-1] = new Tile(texture,position,80, tileIndex,collision);
		std::cout << "Adding new tile to grid" << gridPosition.x << "," << gridPosition.y << std::endl;
	
	}

		

}



