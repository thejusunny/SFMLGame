#include "TileMapEditorState.h"

TileMapEditorState::TileMapEditorState()
{
	this->gridSize = 80.f;
	this->map = new TileMap(this->gridSize, sf::Vector2u(50, 50), 1);
	this->gridSelectionRect.setFillColor(sf::Color::Transparent);
	this->gridSelectionRect.setOutlineColor(sf::Color::Green);
	this->gridSelectionRect.setSize(this->gridSize*sf::Vector2f(1.f,1.f));
	this->gridSelectionRect.setOutlineThickness(1.f);
}

TileMapEditorState::~TileMapEditorState()
{
	delete this->map;
}

void TileMapEditorState::CheckForQuit()
{
}

void TileMapEditorState::Update()
{
	sf::Vector2f mouseViewPos = Mouse::GetMousePosView();

	this->tileSelectorGUI.Update();
	this->gridSelectionRect.setPosition(sf::Vector2f((int)mouseViewPos.x/(int) this->gridSize*this-> gridSize,
		(int)mouseViewPos.y/(int)this->gridSize* this->gridSize));
	this->Input();
}

void TileMapEditorState::Render(sf::RenderTarget* target)
{
	for (auto& object : Drawables::GetDrawables())
		object->Render(*target);
	this->RenderGUI(target);

}

void TileMapEditorState::RenderGUI(sf::RenderTarget* target)
{
	if (!tileSelectorGUI.GetSelectorPanel().getGlobalBounds().contains(Mouse::GetMousePosWindowf()))
	target->draw(this->gridSelectionRect);
	this->tileSelectorGUI.Render(target);

}

void TileMapEditorState::OnEnter()
{
}

void TileMapEditorState::OnExit()
{
}

void TileMapEditorState::Input()
{
	if (Mouse::GetMouseKeyDown(sf::Mouse::Left))
		this->map->AddTile(tileSelectorGUI.GetSelectedTexture(), sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y));
	if (Mouse::GetMouseKeyDown(sf::Mouse::Right))
	{
		
		
		this->map->RemoveTile(sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y));
	}
		
		
		//this->map->RemoveTile( sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y));
}
