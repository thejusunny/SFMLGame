#pragma once
#include <SFML\Graphics.hpp>
#include "GUI.h"
#include "Vector.h"
#include <fstream>
#include "TileEditorTools.h"
#include "TileLayerSelector.h"
class TagEditor

{
public:
	TagEditor(TileLayerSelector *layerSelector,sf::Vector2f position,sf::Vector2f tagBoxSize,int maxTagsinPage);
	void Update();
	void Render(sf::RenderTarget* target);
	const std::vector<std::string> GetTagStrings()const;

private:
	void Input();
	void SaveToFile();
	sf::Font font;
	std::map<std::string, GUI::Button*> buttons;
	std::vector<std::string> LoadFromFile();
	const std::string TagFile = "Tagfile.tag";
	sf::RectangleShape tagEditorRect;
	std::vector<GUI::TextBox*> tagTextBoxes;
	std::vector<std::string> tags;
	sf::Vector2f tagTextSize;
	sf::View mainView;

	bool isScrollBarVisible;
	bool isScrollHeld;
	TileEditorTools* tileEditorTools;
	TileLayerSelector* tileLayerSelector;
	sf::RectangleShape scrollRect;
	sf::RectangleShape scrollBarRect;
	sf::View scrollView;
	sf::View normalView;
	sf::RectangleShape tagPanelRect;
	int maxTagsInPage;
	float currentHeightRatio;
	sf::Vector2f tagBoxSize;
	float Clamp(float value, float max, float min);
};

