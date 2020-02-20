#include "Time.h"

sf::Clock Time::deltaTimeclock;
float Time::deltaTime;
sf::Clock Time::timeClock;
float Time::time;
void Time::UpdateClock()
{
	time = timeClock.getElapsedTime().asSeconds();
	deltaTime = deltaTimeclock.restart().asSeconds();
}
