#include "TagEditor.h"

TagEditor::TagEditor(sf::Vector2f position, sf::Vector2f tagCanvasSize, float tagTextHeight)
{

	this->tagEditorRect.setSize(tagCanvasSize);
	this->tagEditorRect.setPosition(position);
	this->tagEditorRect.setFillColor(sf::Color::Magenta);
	this->tagEditorRect.setOutlineColor(sf::Color::Black);
	this->tagEditorRect.setOutlineThickness(1.f);
	this->tagHeight = tagTextHeight;
	std::vector<std::string> tags = LoadFromFile();
	int noOfTags = tags.size();
	if (noOfTags > 0)
	{
		tagTexts.resize(0);
		for (int i = 0; i < noOfTags; i++)
		{
			tagTexts.push_back(new GUI::TextBox(position + Vector::Up * ((i)* tagTextHeight), sf::Vector2f(tagEditorRect.getSize().x, tagTextHeight), sf::Color::Black, sf::Color::White, sf::Color::Black, tags[i]));

		}
	}
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	buttons["Save"] = new GUI::Button(sf::Vector2f(1730, 200), sf::Vector2f(60, 35), &this->font, "Save", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Add"] = new GUI::Button(sf::Vector2f(1730, 300), sf::Vector2f(60, 35), &this->font, "Add", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Remove"] = new GUI::Button(sf::Vector2f(1730, 370), sf::Vector2f(60, 35), &this->font, "Remove", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	//this->mainView.setCenter(position + Vector::Up * (tagEditorRect.getSize().y / 2));
	//this->mainView.setSize(tagCanvasSize);
	//this->mainView.setViewport(sf::FloatRect(position.x/1920,position.y/1080, tagCanvasSize.x / 1920, tagCanvasSize.y / 1080));




}

void TagEditor::Update()
{
	for (auto i : buttons)
		i.second->Update(InputDevices::Mouse::GetMousePosWindowf());
	for (auto* i : tagTexts)
		i->Update();

	this->Input();
}

void TagEditor::Render(sf::RenderTarget* target)
{
	for (auto i : buttons)
		i.second->Render(target);
	for (auto* i : tagTexts)
		i->Render(target);
}

void TagEditor::Input()
{
	if (this->buttons["Save"]->IsPressed())
	{
		this->SaveToFile();
	
	}
	if (this->buttons["Add"]->IsPressed())
	{
	
		this->tagTexts.push_back(new GUI::TextBox(tagEditorRect.getPosition() + Vector::Up * ((tagTexts.size()) * this->tagHeight), sf::Vector2f(tagEditorRect.getSize().x, this->tagHeight), sf::Color::Black, sf::Color::White, sf::Color::Black, "Empty"));
	}
	if (this->buttons["Remove"]->IsPressed())
	{
	
		this->tagTexts.pop_back();
	}

}

void TagEditor::SaveToFile()
{

	std::ofstream outputStream;
	std::string filePath = "../" + TagFile;
	outputStream.open(filePath);
	if (outputStream.is_open())
	{
		for (auto& i : tagTexts)
		{
			outputStream << i->GetText() << " ";
		}

	}
}

std::vector<std::string> TagEditor::LoadFromFile()
{
	std::ifstream inputStream;
	std::string filePath = "../" +TagFile;

	inputStream.open(filePath);
	std::vector<std::string> tags;
	std::string currentTag;
	tags.resize(0);

	if (inputStream.is_open())
	{
	
		while (inputStream>>currentTag)
		{
			if(currentTag.size()>1)
			tags.push_back(currentTag);
		}
	
	}
	inputStream.close();
	return tags;


}
