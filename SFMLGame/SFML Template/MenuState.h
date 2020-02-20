#pragma once
#include "State.h"
#include "Button.h"
#include "TileMapEditorState.h"
class MenuState : public State
{
private:
	Button* startButton;
	std::map<std::string, Button*> buttons;
	sf::Font font;

public:
	MenuState(std::stack<State*> *states);
	~MenuState();
	void InitFonts();
	void Render(sf::RenderTarget* target);
	void RenderGUI(sf::RenderTarget *target);
	void Update();
	void OnEnter();
	void OnExit();
	void Input();
	void CheckForQuit();
};

