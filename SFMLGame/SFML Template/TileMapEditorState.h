#pragma once
#include "State.h"
#include "TileSelectorGUI.h"
#include "Game.h"
class TileMapEditorState: public State
{
	
protected:
	TileMap *map;
	sf::RectangleShape gridSelectionRect;
	float gridSize;
	TileSelectorGUI tileSelectorGUI;
	std::map<std::string, Button*> buttons;
	sf::Font font;
	float viewMoveSpeed;

public :
	
	TileMapEditorState();
	~TileMapEditorState();
	// Inherited via State
	virtual void CheckForQuit() override;

	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
	virtual void RenderGUI(sf::RenderTarget* target) override;
	virtual void RenderHUD(sf::RenderTarget *target) override;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Input() override;
	
};

