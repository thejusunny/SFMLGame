#include "TagsPanel.h"

TagsPanel::TagsPanel(TileLayerSelector *tileSelector)
{
	this->tagEditor = new TagEditor(tileSelector, sf::Vector2f(1500, 200), sf::Vector2f(200, 30), 12);
}

void TagsPanel::ShowTab()
{
	this->isActive = true;
}

void TagsPanel::HideTab()
{
	this->isActive = false;
}

void TagsPanel::Update()
{
	if (this->isActive)
	{
		this->tagEditor->Update();
	}
}

void TagsPanel::Render(sf::RenderTarget* target)
{
	if (this->isActive)
	{
		this->tagEditor->Render(target);
	}
}
