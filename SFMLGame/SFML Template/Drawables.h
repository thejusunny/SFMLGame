#pragma once
#include <SFML\Graphics.hpp>
#include<list>
class Drawables
{
private:
	static std::list<Drawables*> drawableObjects;

public:
	Drawables();
	virtual void Render(sf::RenderTarget& target)=0;
	static std::list<Drawables*> GetDrawables();
};

