#pragma once
#include <SFML\Graphics.hpp>
#include<iostream>
class Mouse
{
private:
	static sf::Vector2i mousePosScreen;
	static sf::Vector2i mousePosWindow;
	static sf::Vector2f mousePosView;
	static bool keyFlags[2];
	static bool keyDownStates[2];
public:
	const static sf::Vector2i GetMousePosScreen();
	const static sf::Vector2i GetMousePosWindowi();
	const static sf::Vector2f GetMousePosWindowf();
	const static sf::Vector2f GetMousePosView();
	
	static void UpdateMousePosition(sf::RenderWindow* window);

	static bool GetMouseKeyDown(sf::Mouse::Button button);

	static bool GetMouseKeyPress(sf::Mouse::Button button);
	

};

