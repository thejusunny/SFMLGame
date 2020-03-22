#pragma once
#include "State.h"
#include "TileMapEditorState.h"
class MenuState : public State
{
private:

	std::map<std::string, GUI::Button*> buttons;
	sf::Font font;

public:
	MenuState(std::stack<State*> *states);
	~MenuState();
	void InitFonts();
	void Render(sf::RenderTarget* target);// for rendering game objects and other stuff
	void RenderGUI(sf::RenderTarget* target) override;
	void RenderHUD(sf::RenderTarget *target);// for HUD//
	void Update();
	void OnEnter();
	void OnExit();
	void Input();
	void CheckForQuit();
};

