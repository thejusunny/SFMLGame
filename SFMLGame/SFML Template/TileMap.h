#pragma once
#include <SFML\Graphics.hpp>
#include "Drawables.h"
#include "Tile.h"
#include <vector>


class TileMap: public Drawables
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
public :


	TileMap(float gridSize, sf::Vector2u maxSize, unsigned int layers);
	virtual ~TileMap();
	void Render(sf::RenderTarget & target);
	void RemoveTile(sf::Vector2u position);
	void AddTile(sf::Texture* texture,sf::Vector2u position);
	
};

