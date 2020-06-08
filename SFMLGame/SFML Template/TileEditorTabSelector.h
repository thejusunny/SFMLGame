#pragma once
#include "TileSelectorPanel.h"
#include "LoadSavePanel.h"
#include "TagsPanel.h"
class Tab
{
	
public:
	Tab(GUI::Button *btn, SwitchablePanels *p)
	{
		button = btn;
		panel = p;
	
	}
	GUI::Button *button;
	SwitchablePanels *panel;
};

class TileEditorTabSelector
{
public:
	TileEditorTabSelector(TileMap *map);
	void Update();
	void Render(sf::RenderTarget* target);
	template<class PanelType>
	PanelType *GetPanel(std::string name);
	const bool IsMouseEnteringPanel()const;
private:
	sf::Font font;
	sf::Text panelHeadingText;
	sf::RectangleShape sideTabPanel;
	std::map<std::string, Tab*> tabs;
	sf::RectangleShape sideMainPanel;
	GUI::Button* prevButton;
	int currentSelectedTab;
	std::string currentSelectedTabKeyString;
	void Input();
	void InitFonts();
};

template<class PanelType>
inline PanelType *TileEditorTabSelector::GetPanel(std::string name)
{
	return dynamic_cast<PanelType*>( this->tabs[name]->panel);
}
