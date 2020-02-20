#include "Drawables.h"
std::list<Drawables*> Drawables::drawableObjects;
Drawables::Drawables()
{
	drawableObjects.push_front(this);


}

void Drawables::Render(sf::RenderTarget& target)
{
}

std::list<Drawables*> Drawables::GetDrawables()
{
	return drawableObjects;
}
