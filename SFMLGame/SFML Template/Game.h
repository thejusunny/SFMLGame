#pragma once

#include "MenuState.h";

class Game
{
private:
	sf::RenderWindow *renderWindow;


	std::stack<State*> states;
	
	
public :
	Game();
	~Game();
	
	void Run();
	bool ProcessWindowMessages();
	void Update();
	void Render();

};

