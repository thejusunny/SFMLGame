#pragma once
#include <SFML\Graphics.hpp>
class Time
{
private:
	static sf::Clock deltaTimeclock;
	static sf::Clock timeClock;
	
public:
	static float time;
	static float deltaTime;
	static void UpdateClock();

};

