#include "TileMapEditorState.h"

TileMapEditorState::TileMapEditorState()
{
	this->gridSize = 80.f;
	this->viewMoveSpeed = 200.f;
	this->mainView.setSize(sf::Vector2f(1920, 1080));
	this->mainView.setCenter(sf::Vector2f(1920/2, 1080/2));
	this->guiView.setSize(sf::Vector2f(1920, 1080));
	this->guiView.setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
	this->map = new TileMap(this->gridSize, sf::Vector2u(100, 100), 1,&this->tileSelectorGUI);
	this->gridSelectionRect.setFillColor(sf::Color::Transparent);
	this->gridSelectionRect.setOutlineColor(sf::Color::Green);
	this->gridSelectionRect.setSize(this->gridSize*sf::Vector2f(1.f,1.f));
	this->gridSelectionRect.setOutlineThickness(1.f);


	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	//Buttons
	buttons["Load"] = new Button(sf::Vector2f(50, 150), sf::Vector2f(60, 35), &this->font, "Load", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Save"] = new Button(sf::Vector2f(50, 200), sf::Vector2f(60, 35), &this->font, "Save", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
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
	sf::Vector2f mouseViewPos = Mouse::GetMousePosView(&this->mainView);

	if (this->tileSelectorGUI.IsActive())
	this->tileSelectorGUI.Update();
	this->gridSelectionRect.setPosition(sf::Vector2f((int)mouseViewPos.x/(int) this->gridSize*this-> gridSize,
		(int)mouseViewPos.y/(int)this->gridSize* this->gridSize));
	for (auto& button : buttons)
	{
		button.second->Update(Mouse::GetMousePosView(&this->guiView));

	}
	this->Input();
}

void TileMapEditorState::Render(sf::RenderTarget* target)
{
	target->setView(this->mainView);// The map view or scrollable view
	this->map->Render(*target);

	if (!this->tileSelectorGUI.IsMouseEnteringPanel() || !this->tileSelectorGUI.IsActive())
		target->draw(this->gridSelectionRect);

	target->setView(this->guiView);
	this->RenderGUI(target);
	this->RenderHUD(target);


}

void TileMapEditorState::RenderGUI(sf::RenderTarget* target)
{
	for (auto& button : buttons)
		button.second->Render(target);
	if (this->tileSelectorGUI.IsActive())
		this->tileSelectorGUI.Render(target);
}

void TileMapEditorState::RenderHUD(sf::RenderTarget* target)
{
	

}

void TileMapEditorState::OnEnter()
{
}

void TileMapEditorState::OnExit()
{
}

void TileMapEditorState::Input()
{
	
	if (Keyboard::IsKeyDown(sf::Keyboard::Tab))
	{

		if (this->tileSelectorGUI.IsActive())
		{
			this->tileSelectorGUI.SetActive(false);

		}
		else
			this->tileSelectorGUI.SetActive(true);
	}
	
	if (Keyboard::IsKeyPressed(sf::Keyboard::W))
	{
	
		this->mainView.move(0, -this->viewMoveSpeed * Time::deltaTime);
		
	
	}
	else if (Keyboard::IsKeyPressed(sf::Keyboard::S))
	{
		this->mainView.move(0, this->viewMoveSpeed * Time::deltaTime);
	
	}
	else if (Keyboard::IsKeyPressed(sf::Keyboard::A))
	{

		this->mainView.move(-this->viewMoveSpeed * Time::deltaTime, 0);
	}
	else if (Keyboard::IsKeyPressed(sf::Keyboard::D))
	{

		this->mainView.move(this->viewMoveSpeed * Time::deltaTime,0.f);
	}
	if (buttons["Save"]->IsPressed())
	{
		this->map->SaveToFile("TileMap.map");
	}
	if (buttons["Load"]->IsPressed())
	{
		this->map->LoadFromFile("TileMap.map");
	}

	if (!this->tileSelectorGUI.IsMouseEnteringPanel()||!this->tileSelectorGUI.IsActive())
	{
				
		
		if (Mouse::GetMouseKeyDown(sf::Mouse::Left))
		this->map->AddTile(tileSelectorGUI.GetSelectedTexture(), tileSelectorGUI.GetTextureIndex(),sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y));
		if (Mouse::GetMouseKeyDown(sf::Mouse::Right))
		{
			this->map->RemoveTile(sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y));
		}
	}

	
		
}
