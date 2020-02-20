#pragma once
#include <iostream> 
#include <queue>
#include"KeyboardEvent.h"
#include <SFML\Graphics.hpp>

class Keyboard
{
public:

	static const bool IsKeyPressed(sf::Keyboard::Key key);
	static const bool IsKeyDown(sf::Keyboard::Key key);

	std::queue<KeyboardEvent> keyBuffer;
	Keyboard();

private:

	static bool keyDownStates[256];	
	static bool keyFlags[256];

};


