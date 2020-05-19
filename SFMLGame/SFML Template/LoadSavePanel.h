#pragma once
#include "SwitchableTab.h"
#include "TileMap.h"
#include "TagEditor.h"
 
class LoadSavePanel:public SwitchablePanels
{
private:
	std::map<std::string, GUI::Button*> buttons;
	sf::Font font;
	TileMap* tileMap;
	GUI::TextBox* saveTextBox;
	TileSelectorPanel* tileSelector;
	TagEditor* tagEditor;

	void Input();
public:
	LoadSavePanel(TileMap* map, TileSelectorPanel* tileSelectorPanel);

	// Inherited via SwitchablePanels
	 void ShowTab() override;
	 void HideTab() override;
	 void Update() override;
	 void Render(sf::RenderTarget* target) override;
	
};

