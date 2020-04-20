#pragma once
#include <SFML\Graphics.hpp>
#include "TileMap.h"
enum  ToolType
{
	PAINT,SELECT
};
class TileMap;
class TileLayerSelector;
class TileSelectorPanel;
class TileEditorTools
{
public:
	TileEditorTools(TileMap *map,TileSelectorPanel *tileSelector,sf::RectangleShape *mask);
	void Update();
	void Render(sf::RenderTarget* target);
	sf::Vector2u GetGridSelectedIndex();

private:
	std::map<std::string, GUI::Button*> toolButtons;
	sf::RectangleShape gridSelectionRect;
	sf::Font font;
	ToolType currentSelectedTool;
	TileMap* map;
	sf::RectangleShape* tabSelectorMask;
	TileLayerSelector* layerSelector;
	TileSelectorPanel* tileSelectorPanel;
	sf::Vector2u prevPaintTilepos;
	void Input();
};

