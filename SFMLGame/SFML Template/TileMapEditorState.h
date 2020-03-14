#pragma once
#include "State.h"
#include "TileSelectorGUI.h"
#include "Keyboard.h"
#include "TextBox.h"

class TextBox;
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
	sf::RectangleShape sidePanel;
	sf::View mapView;
	sf::Text selectionHeaderText;
	bool collision;
	std::string mouseInfoStr;
	std::string tileInfoStr;
	sf::Text mouseInformationText;
	sf::Text tileInformationText;
	TextBox *textBox;
public :
	
	TileMapEditorState();
	void InitFont();
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
	
	//Math utility extenstion move it to another class
	float Round(float value);
	
};

