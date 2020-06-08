#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "SwitchableTab.h"
#include "TileLayerSelector.h"
#include "TileEditorTools.h"

class TileMap;
class TileLayerSelector;
class TileEditorTools;
class TileSelectorPanel: public SwitchablePanels
{
public:
	void Update();
	void Render(sf::RenderTarget *target);
	TileSelectorPanel(TileMap *map,sf::RectangleShape *tabSelectorMask);
	const sf::RectangleShape GetSelectorPanel()const;
	const bool IsActive()const;
	sf::Texture *GetSelectedTexture();
	sf::Texture* GetTextureFromIndex(int index);
	~TileSelectorPanel();
	int GetTextureIndex();
	bool IsMouseEnteringPanel();
	void SetActive(bool state);
	sf::View guiView;
	void ShowTab();
	void HideTab();
	TileLayerSelector* GetLayerSelector()const;
	TileEditorTools* tileEditorTools;

private:

	void Input();
	void InitFonts();
	void LoadTileGUITextures();
	void MapTexturesToTileSelectorGUI();
	void InitNavigationPanel();
	void InitTileSelectionPanel();


	float tilePadding;
	int selectedTileIndex;

	sf::Font font;
	std::vector <std::vector< sf::RectangleShape>> availableTiles;
	std::map<std::string, GUI::Button*> buttons;
	std::vector <sf::Texture> textures;

	sf::RectangleShape tileSelectorRect;
	sf::RectangleShape tileSelectorPanel;
	sf::RectangleShape tileSelectorNavigationPanel;
	sf::Vector2f tileSelectorPanelSize;
	sf::Vector2f tileSelectorPanelPosition;
	sf::Vector2f tileSize;
	sf::Text pageNoText;
	sf::Text selectionHeaderText;
	TileLayerSelector *layerSelector;


	int noOfRows;
	int noOfCollums;
	int maxTiles;
	int noOfPages;
	int currentPageIndex; 
	

};


