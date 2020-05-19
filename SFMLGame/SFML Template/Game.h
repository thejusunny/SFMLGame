#pragma once
#include "MenuState.h";
#include "CordinateConverter.h"
#include<stack>	
#include"Vector.h"

class Game
{
private:
	sf::RenderWindow *renderWindow;
	std::stack<State*> states;
	static std::string inputString;
	static float timeOflastClear;
	static float timeSinceLastFrame;
	void ClearInputBuffer();
	

public :

	Game();
	~Game();
	
	void Run();
	bool ProcessWindowMessages();
	void Update();
	void Render();
	static const std::string GetInputChar();


};


