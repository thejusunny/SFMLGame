#include "InputDevices.h"

//Mouse 
sf::Vector2i InputDevices::Mouse::mousePosScreen;
sf::Vector2i InputDevices::Mouse::mousePosWindow;
sf::Vector2f InputDevices::Mouse::mousePosView;
bool InputDevices::Mouse::keyDownStates[2];
bool InputDevices::Mouse::keyFlags[2];
sf::RenderWindow* InputDevices::Mouse::window;
float InputDevices::Mouse::timeOfLastKeyPress;
float InputDevices::Mouse::timeSinceLastKeyPress;
InputDevices::Mouse::~Mouse()
{
	delete window;
}
void InputDevices::Mouse::Initialize(sf::RenderWindow* renderWindow)
{
	window = renderWindow;
}
const sf::Vector2i InputDevices::Mouse::GetMousePosScreen()
{
	return sf::Mouse::getPosition();
}
const sf::Vector2i InputDevices::Mouse::GetMousePosWindowi()
{
	mousePosWindow = sf::Mouse::getPosition(*window);
	return mousePosWindow;
}
const sf::Vector2f InputDevices::Mouse::GetMousePosWindowf()
{
	return sf::Vector2f(GetMousePosWindowi().x, GetMousePosWindowi().y);
}
const sf::Vector2f InputDevices::Mouse::GetMousePosView(sf::View* view)
{
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view);// Screen to View pos
	return mousePosView;
}

const sf::Vector2i InputDevices::Mouse::GetMousePosWindowFromView(sf::Vector2f pos, sf::View* view)
{

	return window->mapCoordsToPixel(pos, *view);// view to window
}


bool InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Button button)
{

	bool isPressed = sf::Mouse::isButtonPressed(button);
	timeSinceLastKeyPress = Time::time - timeOfLastKeyPress;

	if (keyFlags[button] == false && isPressed)
	{
		keyFlags[button] = true;
		keyDownStates[button] = true;
		timeOfLastKeyPress = Time::time;
	}
	else if (timeSinceLastKeyPress >= Time::deltaTime)
	{
		keyDownStates[button] = false;


	}
	if (!isPressed)
	{
		keyFlags[button] = false;
	}

	return keyDownStates[button];

}

bool InputDevices::Mouse::GetMouseKeyPress(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

//Keyboard

bool InputDevices::Keyboard::keyDownStates[256];
bool InputDevices::Keyboard::keyFlags[256];
const bool InputDevices::Keyboard::IsKeyPressed(sf::Keyboard::Key key)
{

	return sf::Keyboard::isKeyPressed(key);
}

const bool InputDevices::Keyboard::IsKeyDown(sf::Keyboard::Key key)
{
	bool isPressed = sf::Keyboard::isKeyPressed(key);

	if (keyFlags[key] == false && isPressed)
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

InputDevices::Keyboard::Keyboard()
{

}
