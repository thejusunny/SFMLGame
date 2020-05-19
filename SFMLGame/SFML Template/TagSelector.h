#pragma once
#include "Game.h"
class TagEditor
{
public:
	TagEditor(sf::Vector2f position,sf::Vector2f tagCanvasSize,float tagTextSize);
	void Update();
	void Render(sf::RenderTarget* target);

private:
	void Input();
	sf::RectangleShape tagEditorRect;
	std::vector<GUI::TextBox*> tagTexts;
	sf::Vector2f tagTextSize;
};

