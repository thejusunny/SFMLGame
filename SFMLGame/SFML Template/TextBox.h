#pragma once
#include <SFML\Graphics.hpp>
#include<iostream>
#include "Mouse.h"
#include "Keyboard.h"
#include "Game.h"

class TextBox
{
private:
	sf::RectangleShape textRectShape;
	sf::Text text;
	sf::Color backFillColor;
	sf::Color textColor;
	static sf::RenderWindow* window;
	std::string stringText;
	void PollTextInput();
	bool isSelectionActive;
	sf::Font font;
	float deleteFreq;
	float timer;
	sf::RectangleShape cursor;
	int cursorIndex;
	float characterWidthOffset;
	int fontSize;
	bool IsTextInBounds();
public:
	TextBox(sf::Vector2f position,sf::Vector2f textRectSize, sf::Color textColor, sf::Color backFillColor, 
		sf::Color borderColor, std::string defaultText=" ");
	void Update();
	void Render(sf::RenderTarget *target);
	static void SetWindow(sf::RenderWindow* win);

};

