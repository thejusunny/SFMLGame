#pragma once
#include <SFML\Graphics.hpp>
#include "Drawables.h"
#include "Tile.h"
#include <vector>
#include<fstream>
#include "TileSelectorPanel.h"
#include "CordinateConverter.h"
class TileSelectorPanel;
class TileMap: public Drawables
{
private:	
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	sf::View* view;
	sf::RectangleShape collisionRect;
public :
	TileMap(float gridSize, sf::Vector2u maxSize, unsigned int layers,sf::View *view);
	virtual ~TileMap();
	const int GetTileLayer()const;
	void UpdateLayers(sf::Vector2u index, std::vector<Tile*>tiles);
	void Render(sf::RenderTarget & target);
	void RemoveTile(sf::Vector2u position,int selectedLayer);
	void AddTile(sf::Texture* texture,int layerNo, int tileIndex, sf::Vector2u position,bool collision );
	void SaveToFile(std::string fileName);
	void LoadFromFile(std::string fileName, TileSelectorPanel *tileSelectorMap);
	std::vector<std::vector<std::vector<Tile*>>> GetMap();
	void ClearMap();
	void Update();
	const float GetGridSizeF()const;
	sf::View* GetMapView()const;
	void UpdateTiles(sf::Vector2u tileIndex, std::vector<Tile*>tiles);
	Tile* GetTopTile(sf::Vector2u tileIndex);
};

