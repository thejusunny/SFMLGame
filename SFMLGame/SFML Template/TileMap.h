#pragma once
#include <SFML\Graphics.hpp>
#include "Drawables.h"
#include "Tile.h"
#include <vector>
#include<fstream>
#include "TileSelectorGUI.h"
#include "CordinateConverter.h"
class TileMap: public Drawables
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	TileSelectorGUI *tileSelectionGUI;// used to get the texture buffer so u dont have to load from file 
	sf::RectangleShape *rectMask; //
	sf::View* view;
	sf::RectangleShape collisionRect;
public :
	TileMap(float gridSize, sf::Vector2u maxSize, unsigned int layers,TileSelectorGUI *gui,sf::RectangleShape *mask,sf::View *view);
	virtual ~TileMap();
	void Render(sf::RenderTarget & target);
	void RemoveTile(sf::Vector2u position);
	void AddTile(sf::Texture* texture, int tileIndex, sf::Vector2u position,bool collision );
	void SaveToFile(std::string fileName);
	void LoadFromFile(std::string fileName);	
	void ClearMap();
	void Update();
	
};

