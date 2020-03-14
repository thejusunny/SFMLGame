#pragma once
#include <SFML\Graphics.hpp>
static class CordinateConverter
{
private:
	static sf::RenderWindow *window;
public:
	static void Initialize(sf::RenderWindow* window);
	static sf::Vector2i ViewToScreenPoint(sf::Vector2f postion,sf::View *view);
	static sf::Vector2f ScreenToViewPoint(sf::Vector2i pos, sf::View* view);
	static sf::FloatRect viewToScreenRect(sf::FloatRect rect, sf::View* view);

};

