#include "Mouse.h"
sf::Vector2i Mouse::mousePosScreen;
sf::Vector2i Mouse::mousePosWindow;
sf::Vector2f Mouse::mousePosView;
bool Mouse::keyDownStates[2];
bool Mouse::keyFlags[2];
sf::RenderWindow* Mouse::window;
Mouse::~Mouse()
{
	delete window;
}
void Mouse::Initialize(sf::RenderWindow* renderWindow)
{
	window = renderWindow;
}
const sf::Vector2i Mouse::GetMousePosScreen()
{
	return sf::Mouse::getPosition();
}
const sf::Vector2i Mouse::GetMousePosWindowi()
{
	mousePosWindow = sf::Mouse::getPosition(*window);
	return mousePosWindow;
}
const sf::Vector2f Mouse::GetMousePosWindowf()
{
	return sf::Vector2f(GetMousePosWindowi().x, GetMousePosWindowi().y);
}
const sf::Vector2f Mouse::GetMousePosView( sf::View *view)
{
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window),*view);// Screen to world pos
	return mousePosView;
}

const sf::Vector2i Mouse::GetMousePosWindowFromView(sf::Vector2f pos,sf::View* view)
{
	
	return window->mapCoordsToPixel(pos, *view);
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
