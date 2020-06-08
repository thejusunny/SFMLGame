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
	void SetSelectorRect(sf::Texture *tex);
	void UpdateTags(std::vector<std::string> tags);// for now completely map the textbox array to drop down , later change it to have callbacks from textbox 
private:
	std::map<std::string, GUI::Button*> toolButtons;
	sf::Texture selectToolTex, painToolTex;
	sf::Text toolHeaderText;
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

