#pragma once
#include <SFML\Graphics.hpp>
#include "GUI.h"
#include "Vector.h"
#include <fstream>

class TagEditor
{
public:
	TagEditor(sf::Vector2f position,sf::Vector2f tagCanvasSize,float tagTextHeight);
	void Update();
	void Render(sf::RenderTarget* target);

private:
	void Input();
	void SaveToFile();
	sf::Font font;
	std::map<std::string, GUI::Button*> buttons;
	std::vector<std::string> LoadFromFile();
	const std::string TagFile = "Tagfile.tag";
	sf::RectangleShape tagEditorRect;
	std::vector<GUI::TextBox*> tagTexts;
	sf::Vector2f tagTextSize;
	sf::View mainView;
	sf::RectangleShape scrollRect;
	sf::RectangleShape scrollBarRect;
	float tagHeight;
	bool isScrollBarVisible;
	bool isScrollHeld;
};

