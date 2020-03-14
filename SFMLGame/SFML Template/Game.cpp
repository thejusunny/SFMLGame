#include "Game.h"
std::string Game::inputString;
float Game::timeOflastClear;
float Game::timeSinceLastFrame;
Game::Game()
{

	

	this->renderWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "MyGame");
	TextBox::SetWindow(this->renderWindow);
	Mouse::Initialize(this->renderWindow);
	CordinateConverter::Initialize(this->renderWindow);
	inputString = "";
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
		else if (event.type == sf::Event::TextEntered)
		{
			if(event.text.unicode!=8)
			inputString = event.text.unicode;

		}
		
	}

	return true;
}


void Game::Update()
{
	

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
	this->renderWindow->setView(this->renderWindow->getDefaultView());
	this->renderWindow->display();

}

const  std::string
Game::GetInputChar()
{
	std::string temp = inputString;
	inputString = "";
	/*timeSinceLastFrame = Time::time - timeOflastClear;
	if (timeSinceLastFrame >= Time::deltaTime)
	{
		inputString = "";
		timeOflastClear = Time::time;
	}*/
	return temp;
}
