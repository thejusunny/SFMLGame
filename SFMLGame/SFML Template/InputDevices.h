#pragma once
#include <SFML\Graphics.hpp>
#include<iostream>
#include "Time.h"
#include<math.h>

namespace InputDevices
{
	
	class Mouse
	{
	private:
		static sf::Vector2i mousePosScreen;
		static sf::Vector2i mousePosWindow;
		static sf::Vector2f mousePosView;
		static bool keyFlags[2];
		static bool keyDownStates[2];
		static sf::RenderWindow* window;
		static float timeOfLastKeyPress;
		static float timeSinceLastKeyPress;
		static long lastFrameNo;
		static sf::Vector2f lastMousePosition;
		static sf::Vector2f mousePosCurrent;

	public:
		~Mouse();
		static void Initialize(sf::RenderWindow* renderWindow);
		const static sf::Vector2i GetMousePosScreen();
		const static sf::Vector2i GetMousePosWindowi();
		const static sf::Vector2f GetMousePosWindowf();
		const static sf::Vector2f GetMousePosView(sf::View* view);
		const static sf::Vector2i GetMousePosWindowFromView(sf::Vector2f pos, sf::View* view);
		const static sf::Vector2f GetMouseDelta();
		const static float GetMouseSpeedVertical();

		static bool GetMouseKeyDown(sf::Mouse::Button button);

		static bool GetMouseKeyPress(sf::Mouse::Button button);


	};

	class Keyboard
	{
	public:

		static const bool IsKeyPressed(sf::Keyboard::Key key);
		static const bool IsKeyDown(sf::Keyboard::Key key);

		Keyboard();

	private:

		static bool keyDownStates[256];
		static bool keyFlags[256];

	};


}

