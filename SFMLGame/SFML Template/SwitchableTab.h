#pragma once
#include <SFML\Graphics.hpp>
#include "GUI.h"
class SwitchablePanels
{
protected:
	bool isActive = true;

public :
	virtual void ShowTab()=0;
	virtual void HideTab()=0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget *target) = 0;
	
};

