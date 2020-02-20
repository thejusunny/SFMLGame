#pragma once

#include <SFML\Graphics.hpp>


class InputHandler
{
private :


public :

	InputHandler();
	
	bool ReadInputs(sf::RenderWindow *window);

	 bool GetKeyDown(sf::Keyboard::Key key);

};

