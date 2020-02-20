#pragma once
#include "TileMap.h"

#include"GameObject.h"
#include "Drawables.h"
#include "Time.h"
#include<iostream>
#include<stack>
#include "Mouse.h"
class State
{
private :
	bool quit = false;
protected:
	std::stack<State*> *gameStates;
	
public:
	
	const bool GetQuit()const;
	virtual void CheckForQuit()=0;
	virtual void Update() = 0;// updates all the elements in that state
	virtual void Render(sf::RenderTarget* target) = 0;// renders all the object in that state
	virtual void RenderGUI(sf::RenderTarget *target)=0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Input() = 0;
	void EndGame();

};

