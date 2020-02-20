#pragma once
#include <SFML\Graphics.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "Mouse.h"
#include "Button.h"
class TileSelectorGUI
{
public:
	void Update();
	void Render(sf::RenderTarget *target);
	TileSelectorGUI();
	const sf::RectangleShape GetSelectorPanel()const;
	const bool IsActive()const;
	sf::Texture *GetSelectedTexture();
private:

	void Input();
	bool isActive = false;
	float tilePadding;
	int selectedTileIndex;
	std::vector <sf::RectangleShape> availableTiles;
	std::vector <sf::Texture> textures;
	sf::RectangleShape tileSelectorRect;
	sf::RectangleShape tileSelectorPanel;
	sf::Vector2f tileSelectorPanelSize;
	sf::Vector2f tileSelectorPanelPosition;
	sf::Vector2f selectionTileSize;
	int noOfRows;
	int noOfCollums;
	

};

