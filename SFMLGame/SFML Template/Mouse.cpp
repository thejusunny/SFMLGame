#include "Mouse.h"
sf::Vector2i Mouse::mousePosScreen;
sf::Vector2i Mouse::mousePosWindow;
sf::Vector2f Mouse::mousePosView;
bool Mouse::keyDownStates[2];
bool Mouse::keyFlags[2];
const sf::Vector2i Mouse::GetMousePosScreen()
{
	return mousePosScreen;
}
const sf::Vector2i Mouse::GetMousePosWindowi()
{
	return mousePosWindow;
}
const sf::Vector2f Mouse::GetMousePosWindowf()
{
	return sf::Vector2f(mousePosWindow.x,mousePosWindow.y);
}
const sf::Vector2f Mouse::GetMousePosView()
{
	return mousePosView;
}
void Mouse::UpdateMousePosition(sf::RenderWindow* window)
{

	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

}

bool Mouse::GetMouseKeyDown(sf::Mouse::Button button)
{
	
	bool isPressed = sf::Mouse::isButtonPressed(button);

	if (keyFlags[button] == false && isPressed)
	{
		keyFlags[button] = true;
		keyDownStates[button] = true;

	}
	else
	{
		keyDownStates[button] = false;


	}
	if (!isPressed)
	{
		keyFlags[button] = false;
	}

	return keyDownStates[button];
	
}

bool Mouse::GetMouseKeyPress(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}
