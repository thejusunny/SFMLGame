#pragma once
#include <SFML\Graphics.hpp>
#include "Drawables.h"
#include "Tile.h"
#include <vector>
#include<fstream>
#include "TileSelectorGUI.h"
class TileMap: public Drawables
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	TileSelectorGUI *tileSelectionGUI;// used to get the texture buffer so u dont have to load from file 
public :
	TileMap(float gridSize, sf::Vector2u maxSize, unsigned int layers,TileSelectorGUI *gui);
	virtual ~TileMap();
	void Render(sf::RenderTarget & target);
	void RemoveTile(sf::Vector2u position);
	void AddTile(sf::Texture* texture, int tileIndex, sf::Vector2u position);
	void SaveToFile(std::string fileName);
	void LoadFromFile(std::string fileName);	
	void ClearMap();
};

