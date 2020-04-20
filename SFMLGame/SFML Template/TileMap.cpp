#include "TileMap.h"
#include<iostream>
TileMap::TileMap( float gridSize, sf::Vector2u maxSize, unsigned int layers,sf::View *view)
{
	this->gridSizeF = gridSize;
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
				this->map[x][y].resize(this->layers-1);
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

void TileMap::LoadFromFile(std::string fileName,TileSelectorPanel *tileSelectorMap)
{
	/*
	MAXSIZE X,Y- Size of the whole TileMap X x Y
	GRIDSIZE - Size of Each Tile
	LAYERS

	X Y Z positions, TextureIndex, Collision

	*/
	std::cout <<"Grid"+ gridSizeU;

	this->ClearMap();
	this->gridSizeU = static_cast<unsigned>(gridSizeF);
	this->layers = layers;
	this->maxSize = maxSize;
	this->map.resize(this->maxSize.x-1);
	
	std::ifstream inputStream;
	std::string filePath = "../" + fileName;
	inputStream.open(filePath);
	unsigned x=0, y=0, z=0; 

	int textureIndex=0;
	bool collision;

	


	if (inputStream.is_open())
	{
		inputStream >> this->maxSize.x >> this->maxSize.y >> this->gridSizeU >> this->layers;
		this->layers = 4;
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			this->map.push_back(std::vector< std::vector<Tile*>>());
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y-1);
				this->map[x].push_back(std::vector<Tile*>()); // 2nd vector
				for (size_t z = 0; z < layers; z++)
				{
					this->map[x][y].resize(this->layers-1);
					this->map[x][y].push_back(NULL); // 3rd vector

				}
			}
		}
	
		std::string texturePath = "";
		while (inputStream>>x>>y>>z>> textureIndex >>collision)
		{
		
			std::cout << x<<" "<<y<<" "<<z<<" "<< textureIndex <<"\n";
			
			this->map[x][y][z] = new Tile(tileSelectorMap->GetTextureFromIndex(textureIndex),0,sf::Vector2u(x*gridSizeU,y*gridSizeU), gridSizeU, textureIndex,collision);
			if(collision)
			this->collisionRect.setPosition(map[x][y][z]->GetPosition());
		}

		

	}
	inputStream.close();
}

std::vector<std::vector<std::vector<Tile*>>> TileMap::GetMap()
{
	return this->map;
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

const float TileMap::GetGridSizeF() const
{
	return gridSizeF;
}

sf::View* TileMap::GetMapView() const
{
	return this->view;
}

void TileMap::UpdateTiles(sf::Vector2u tileIndex, std::vector<Tile*> tiles)
{
	this->map[tileIndex.x][tileIndex.y] = tiles;
}

Tile* TileMap::GetTopTile(sf::Vector2u tileIndex)
{
	return this->map[tileIndex.x][tileIndex.y][3];
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


const int TileMap::GetTileLayer() const
{
	return 0;
}

void TileMap::UpdateLayers(sf::Vector2u index, std::vector<Tile*> tiles)
{
	this->map[index.x][index.y] = tiles;
}

void TileMap::Render(sf::RenderTarget &target)
{

	for (int x = 0; x<this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
		
			for (int z = layers-1; z >= 0; z--)
			{
				if (map[x][y][z] != nullptr)// if the tile is not deleted or empty
				{

					map[x][y][z]->Render(target);
					if (map[x][y][z]->IsCollidable())
					{
						this->collisionRect.setPosition(map[x][y][z]->GetPosition());
						target.draw(this->collisionRect);
					}
				}
			}
		}
	}
	//for (auto& x: this->map)
	//{
	//
	//	for (auto& y : x)
	//	{
	//		for (auto *z : y)
	//		{
	//			if(z !=nullptr )// if the tile is not deleted or empty
	//			{ 
	//				
	//				z->Render(target);
	//				if (z->IsCollidable())
	//				{
	//					this->collisionRect.setPosition(z->GetPosition());
	//					target.draw(this->collisionRect);
	//				}
	//				
	//			}
	//			
	//		
	//		}
	//	}
	//}
	
	
}

void TileMap::RemoveTile(sf::Vector2u position,int selectedLayer)
{
	sf::Vector2u gridPosition;
	gridPosition.x = position.x / gridSizeU;
	gridPosition.y = position.y / gridSizeU;
	std::cout << "Removing Tile";
	if (this->map[gridPosition.x][gridPosition.y][selectedLayer -1] != NULL)
	{
		delete this->map[gridPosition.x][gridPosition.y][selectedLayer -1];
		this->map[gridPosition.x][gridPosition.y][selectedLayer -1] = NULL;
	}
}


void TileMap::AddTile( sf::Texture* texture,int layerNo, int tileIndex, sf::Vector2u position, bool collision)
{
	sf::Vector2u gridPosition;

	gridPosition.x = position.x / gridSizeU;
	gridPosition.y = position.y / gridSizeU;
	
	Tile *tileToInsert = new Tile(texture, layerNo, position, 80, tileIndex, collision);

	if (this->map[gridPosition.x][gridPosition.y][0] == NULL)
	{
	
		this->map[gridPosition.x][gridPosition.y][0] = tileToInsert;
		return;
	
	}
	int indexToDelete = -1;
	std::vector <Tile*> tiles = this->map[gridPosition.x][gridPosition.y];
	for (int z = 0; z < layers;z++)// find the closest empty slot and delete it
	{
			if (map[gridPosition.x][gridPosition.y][z] == NULL)
			indexToDelete = z;
				
	}
	if (indexToDelete > 0)
	{
		tiles.erase(tiles.begin() + indexToDelete);
		tiles.insert(tiles.begin() ,tileToInsert);
		this->map[gridPosition.x][gridPosition.y] = tiles;
	}
	//for (int i = 0; i < this->layers; i++)
	//{
	//	
	//	if (this->map[gridPosition.x][gridPosition.y][i] == NULL)
	//	{
	//		this->map[gridPosition.x][gridPosition.y][i] = new Tile(texture, layerNo, position, 80, tileIndex, collision);
	//		//std::cout << "Adding new tile to grid" << gridPosition.x << "," << gridPosition.y << std::endl;
	//		break;
	//	}


	//}

		

}



