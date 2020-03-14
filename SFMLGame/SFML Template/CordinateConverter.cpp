#include "CordinateConverter.h"
sf::RenderWindow* CordinateConverter::window;
void CordinateConverter::Initialize(sf::RenderWindow* win)
{
	window = win;
}

sf::Vector2i CordinateConverter::ViewToScreenPoint(sf::Vector2f postion, sf::View* view)
{
	return  window->mapCoordsToPixel(postion, *view);
}


sf::Vector2f CordinateConverter::ScreenToViewPoint(sf::Vector2i pos, sf::View* view)
{

	return  window->mapPixelToCoords(pos, *view);
	
}

sf::FloatRect CordinateConverter::viewToScreenRect(sf::FloatRect rect, sf::View* view)
{
	sf::FloatRect newRect;
	newRect.top  = ViewToScreenPoint(sf::Vector2f(rect.left,rect.top),view).y;
	newRect.left = ViewToScreenPoint(sf::Vector2f(rect.left, rect.top), view).x;
	newRect.width = newRect.left + rect.width;
	newRect.height = newRect.top + rect.height;

	return newRect;
}
