#include "Keyboard.h"

bool Keyboard::keyDownStates[256];
bool Keyboard::keyFlags[256];
const bool Keyboard::IsKeyPressed(sf::Keyboard::Key key)
{

	return sf::Keyboard::isKeyPressed(key);
}

const bool Keyboard::IsKeyDown(sf::Keyboard::Key key)
{
		bool isPressed = sf::Keyboard::isKeyPressed(key);
	
		if (keyFlags[key] == false&&isPressed)
		{
			keyFlags[key] = true;
			keyDownStates[key] = true;

		}
		else
		{
			keyDownStates[key] = false;


		}
		if (!isPressed)
		{
			keyFlags[key] = false;
		}
		return keyDownStates[key];
}

Keyboard::Keyboard()
{
	
}

