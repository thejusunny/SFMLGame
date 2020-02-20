#include "Game.h"

Game::Game() 
{
	this->renderWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "MyGame");
	states.push(new MenuState(&this->states));
}

Game::~Game()
{
	delete this->renderWindow;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::Run()
{
	
	//Game Loop
	while (true)
	{
		Time::UpdateClock();
		Mouse::UpdateMousePosition(this->renderWindow);
		/*std::cout << Time::deltaTime<<"\n";
		std::cout << Time::time;
	
		system("cls");*/
		ProcessWindowMessages();
		Update();
		Render();
	
		
	}
	
}

bool Game::ProcessWindowMessages()
{
	sf::Event event;
	while (this->renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			renderWindow->close();
			exit(0);
		}
	}
	return true;
}

void Game::Update()
{
	for (auto& object : GameObject::GetAllGameObjects())
		object->Update();	

	if (!this->states.empty())
	{
		this->states.top()->Update();
		if (this->states.top()->GetQuit())
		{
			this->states.top()->OnExit();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
		this->renderWindow->close();

}

void Game::Render()
{
	this->renderWindow->clear();

	if (!this->states.empty())
		states.top()->Render(renderWindow);
	this->renderWindow->display();

}
