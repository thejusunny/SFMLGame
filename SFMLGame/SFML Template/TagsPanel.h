#pragma once
#include "SwitchableTab.h"
#include "TagEditor.h"
#include "TileMap.h"
class TagsPanel: public SwitchablePanels
{
public :
	TagsPanel(TileLayerSelector* tileEditorTools);
	// Inherited via SwitchablePanels
	void ShowTab() override;
	void HideTab() override;
	void Update() override;
	void Render(sf::RenderTarget* target) override;

private:
	TagEditor* tagEditor;
	
	
};

