#include "TileMapEditorState.h"

TileMapEditorState::TileMapEditorState()
{
	InitFont();
	this->gridSize = 80.f;
	this->viewMoveSpeed = 300.f;
	this->sidePanel.setSize(sf::Vector2f(500, 1080));
	this->sidePanel.setPosition(sf::Vector2f(1500, 0));
	this->sidePanel.setFillColor(sf::Color(0, 0, 255, 30));

	//GUI stats text

	this->mouseInformationText.setPosition(1540, 700);
	this->tileInformationText.setPosition(1540, 750);
	this->mouseInformationText.setFont(this->font);
	this->tileInformationText.setFont(this->font);
	this->mouseInformationText.setFillColor(sf::Color::White);
	this->mouseInformationText.setCharacterSize(16);
	this->tileInformationText.setCharacterSize(16);

	//this->mainView.reset(sf::FloatRect(0, 0, 1600, 1080));
	float mapViewSize =this->sidePanel.getGlobalBounds().left;
	this->mapView.setSize(mapViewSize, 1080);
	float widthOffsetPerc = (mapViewSize / 1920);
	this->mapView.setViewport(sf::FloatRect(0, 0, widthOffsetPerc, 1));
	this->mapView.setCenter(sf::Vector2f(mapViewSize/2, 1080/2));
	this->guiView.setSize(sf::Vector2f(1920, 1080));
	this->guiView.setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
	this->map = new TileMap(this->gridSize, sf::Vector2u(100, 100), 1,&this->tileSelectorGUI,&this->sidePanel,&this->mapView);
	this->gridSelectionRect.setFillColor(sf::Color::Transparent);
	this->gridSelectionRect.setOutlineColor(sf::Color::Green);
	this->gridSelectionRect.setSize(this->gridSize*sf::Vector2f(1.f,1.f));
	this->gridSelectionRect.setOutlineThickness(1.f);

	this->selectionHeaderText.setFont(this->font);
	this->selectionHeaderText.setFillColor(sf::Color::White);
	this->selectionHeaderText.setString("Tile Selectoion panel");
	this->selectionHeaderText.setCharacterSize(22);
	this->selectionHeaderText.setPosition(sf::Vector2f(1540, 50));
	//Buttons
	buttons["Load"] = new Button(sf::Vector2f(1540, 650), sf::Vector2f(60, 35), &this->font, "Load", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Save"] = new Button(sf::Vector2f(1660, 650), sf::Vector2f(60, 35), &this->font, "Save", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	this->textBox = new TextBox(sf::Vector2f(500, 500), sf::Vector2f(300, 50), sf::Color::Black, sf::Color::White, sf::Color::Black);
}

void TileMapEditorState::InitFont()
{
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
}

TileMapEditorState::~TileMapEditorState()
{
	delete this->map;
	delete this-> textBox;
}

void TileMapEditorState::CheckForQuit()
{
}



void TileMapEditorState::Update()
{
	sf::Vector2f mouseViewPos = Mouse::GetMousePosView(&this->mapView);
	this->mouseInfoStr = "MouseViewPos  x - " +std::to_string(static_cast<int> (mouseViewPos.x)) + " y - "+ std::to_string(static_cast<int> ( mouseViewPos.y))+"\n";
	this->mouseInfoStr += "MouseWindowPos  x - " + std::to_string( Mouse::GetMousePosWindowi().x) + " y - " + std::to_string(Mouse::GetMousePosWindowi().y)+ "\n";
	this->mouseInformationText.setString(this->mouseInfoStr);

	this->tileInfoStr = "TilePosGrid  x - " + std::to_string(static_cast<int>(this->gridSelectionRect.getPosition().x/this->gridSize)) + " y - " + std::to_string(static_cast<int>( this->gridSelectionRect.getPosition().y/ this->gridSize))+"\n";
	this->tileInfoStr += "Collider State  - " + std::to_string( this->collision)+ "\n";
	this->tileInformationText.setString(tileInfoStr);
	if (this->tileSelectorGUI.IsActive())
	this->tileSelectorGUI.Update();
	this->gridSelectionRect.setPosition(sf::Vector2f((int)mouseViewPos.x/(int) this->gridSize*this-> gridSize,
		(int)mouseViewPos.y/(int)this->gridSize* this->gridSize));
	
	
	for (auto& button : buttons)
	{
		button.second->Update(Mouse::GetMousePosView(&this->guiView));

	}
	
	
	this->textBox->Update();
	this->map->Update();
	this->Input();
}

void TileMapEditorState::Render(sf::RenderTarget* target)
{
	target->setView(this->mapView);// The map view or scrollable view
	this->map->Render(*target);
	if (!this->tileSelectorGUI.IsMouseEnteringPanel() || !this->tileSelectorGUI.IsActive())
		target->draw(this->gridSelectionRect);

	target->setView(this->guiView);
	this->RenderHUD(target);
	this->RenderGUI(target);



}

void TileMapEditorState::RenderGUI(sf::RenderTarget* target)
{
	
	
	for (auto& button : buttons)
		button.second->Render(target);
	if (this->tileSelectorGUI.IsActive())
		this->tileSelectorGUI.Render(target);
	this->textBox->Render(target);
}

void TileMapEditorState::RenderHUD(sf::RenderTarget* target)
{
	target->draw(this->sidePanel);
	target->draw(this->selectionHeaderText);
	target->draw(this->mouseInformationText);
	target->draw(this->tileInformationText);

}

void TileMapEditorState::OnEnter()
{
}

void TileMapEditorState::OnExit()
{
}

void TileMapEditorState::Input()
{
	if (Keyboard::IsKeyDown(sf::Keyboard::B))
	{
		this->collision = !this->collision;
	}
	
	
	if (Keyboard::IsKeyPressed(sf::Keyboard::W))
	{
	
		if (Keyboard::IsKeyPressed(sf::Keyboard::LShift))
			this->mapView.move(0, -this->viewMoveSpeed*2 * Time::deltaTime);
		else
		this->mapView.move(0, -this->viewMoveSpeed * Time::deltaTime);
		
	
	}
	else if (Keyboard::IsKeyPressed(sf::Keyboard::S))
	{
		if (Keyboard::IsKeyPressed(sf::Keyboard::LShift))
			this->mapView.move(0, this->viewMoveSpeed * 2 * Time::deltaTime);
		else
		this->mapView.move(0, this->viewMoveSpeed * Time::deltaTime);
	
	}
	else if (Keyboard::IsKeyPressed(sf::Keyboard::A))
	{
		if (Keyboard::IsKeyPressed(sf::Keyboard::LShift))
			this->mapView.move(-this->viewMoveSpeed*2 * Time::deltaTime, 0);
		else
		this->mapView.move(-this->viewMoveSpeed * Time::deltaTime, 0);
	}
	else if (Keyboard::IsKeyPressed(sf::Keyboard::D))
	{
		if (Keyboard::IsKeyPressed(sf::Keyboard::LShift))
			this->mapView.move(this->viewMoveSpeed*2 * Time::deltaTime, 0.f);
		else
		this->mapView.move(this->viewMoveSpeed * Time::deltaTime,0.f);
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
		{
			
			this->map->AddTile(tileSelectorGUI.GetSelectedTexture(), tileSelectorGUI.GetTextureIndex(), sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y), this->collision);
		}
		if (Mouse::GetMouseKeyDown(sf::Mouse::Right))
		{
			this->map->RemoveTile(sf::Vector2u(this->gridSelectionRect.getPosition().x, this->gridSelectionRect.getPosition().y));
		}
	}

	
		
}

float TileMapEditorState::Round(float value)
{
	float truncated = (float)((int)value * 100) / 100;
	return truncated;

}
