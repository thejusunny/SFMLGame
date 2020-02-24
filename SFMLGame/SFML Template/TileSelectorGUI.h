#pragma once
#include <SFML\Graphics.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "Mouse.h"
#include "Button.h"
#include "Keyboard.h"
class TileSelectorGUI
{
public:
	void Update();
	void Render(sf::RenderTarget *target);
	TileSelectorGUI();
	const sf::RectangleShape GetSelectorPanel()const;
	const bool IsActive()const;
	sf::Texture *GetSelectedTexture();
	sf::Texture* GetTextureFromIndex(int index);
	~TileSelectorGUI();
	int GetTextureIndex();
	bool IsMouseEnteringPanel();
	void SetActive(bool state);
	sf::View guiView;
private:

	void Input();
	void InitFonts();
	void LoadTileGUITextures();
	void MapTexturesToTileSelectorGUI();
	void InitNavigationPanel();
	void InitTileSelectionPanel();

	bool isActive = false;
	float tilePadding;
	int selectedTileIndex;
	sf::Font font;
	std::vector <std::vector< sf::RectangleShape>> availableTiles;
	std::map<std::string, Button*> buttons;
	std::vector <sf::Texture> textures;
	sf::RectangleShape tileSelectorRect;
	sf::RectangleShape tileSelectorPanel;
	sf::RectangleShape tileSelectorNavigationPanel;
	sf::Vector2f tileSelectorPanelSize;
	sf::Vector2f tileSelectorPanelPosition;
	sf::Vector2f tileSize;
	sf::Text pageNoText;
	int noOfRows;
	int noOfCollums;
	int maxTiles;
	int noOfPages;
	int currentPageIndex; 
	

};

