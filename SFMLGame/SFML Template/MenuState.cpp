#include "MenuState.h"

MenuState::MenuState(std::stack<State*> *states)
{
	this->gameStates = states;
	this->guiView.setSize(sf::Vector2f(1920, 1080));
	this->guiView.setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
	OnEnter();
	InitFonts();
	buttons["Start_Button"] = new Button(sf::Vector2f(100, 200), sf::Vector2f(150, 50), &this->font, "Start", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Editor_Button"] = new Button(sf::Vector2f(100, 300), sf::Vector2f(250, 50), &this->font, "Tile Map Editor", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Exit_Button"] = new Button(sf::Vector2f(100, 400), sf::Vector2f(150, 50), &this->font, "Exit", sf::Color::White, sf::Color::Cyan, sf::Color::Red);

}



MenuState::~MenuState()
{

	for (auto &it:buttons)
		delete &it;
}

void MenuState::InitFonts()
{
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}

}

void MenuState::Render(sf::RenderTarget *target)
{
	target->setView(this->guiView);
	this->RenderHUD(target);
}

void MenuState::RenderGUI(sf::RenderTarget* target)
{
}

void MenuState::RenderHUD(sf::RenderTarget *target)
{

	for (auto& button : buttons)
		button.second->Render(target);// second means the value, first means key

	//Selector rectangle


}

void MenuState::Update()
{
	for (auto& button : buttons)
	{
		button.second->Update(Mouse::GetMousePosView(&this->guiView));

	}
	Input();


}

void MenuState::OnEnter()
{
	
}

void MenuState::OnExit()
{
}

void MenuState::Input()
{
	if (buttons["Editor_Button"]->IsPressed())
	{
		this->gameStates->push(new TileMapEditorState());
	}

	CheckForQuit();
}

void MenuState::CheckForQuit()
{
	if (buttons["Exit_Button"]->IsPressed())
	{
		this->EndGame();

	}
}
