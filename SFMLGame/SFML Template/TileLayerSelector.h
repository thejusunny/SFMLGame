#pragma once
#include <SFML\Graphics.hpp>
#include<vector>
#include"GUI.h"
#include "Tilemap.h"
class Layer
{
public :
	sf::Text tileType;
	void Render(sf::RenderTarget* target);
	Layer(int layerIndex, sf::Vector2f layerRectPos, sf::Vector2f layerRectSize,sf::Font &font);
private:

	sf::RectangleShape layerRects;
	sf::Text layerName;
};
class TileMap;
class TileLayerSelector
{
public:
	void Update();
	void Render(sf::RenderTarget *target);
	void Input();
	void UpdateLayerPanel(std::vector<Tile*>tiles,sf::Vector2u tileIndex);
	void UpdateTags(std::vector<std::string> tags);
	TileLayerSelector(TileMap *map);
private:
	sf::RectangleShape mainPanel;
	std::vector<Layer*> layers;
	std::vector<sf::RectangleShape> tileIcons;
	TileMap* map;
	GUI::DropDownBox* layerDropDownBox;
	sf::RectangleShape selectedRect;
	int currentSelectedLayer;
	int mouseHeldIndex;
	int noOfLayers;
	bool iconHeld;
	bool iconSeleceted;
	int selectedIconIndex;
	sf::Font font;
	std::vector<Tile*> tileBuffer;
	sf::Vector2u tileIndex;
	sf::Color selectedOutlineColor;
	float selectedOutlineThickness;
	void UpdateLayerIcons();
	void UpdateSelectedTile(int index);

};

