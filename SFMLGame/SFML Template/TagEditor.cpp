#include "TagEditor.h"

TagEditor::TagEditor(TileLayerSelector* layerSelector, sf::Vector2f position, sf::Vector2f tagBoxSize, int maxTagsPerPage)
{
	this->tileLayerSelector = layerSelector;
	this->tagEditorRect.setSize(sf::Vector2f(tagBoxSize.x,tagBoxSize.y* maxTagsPerPage));
	this->tagEditorRect.setPosition(position);
	this->tagEditorRect.setFillColor(sf::Color::Magenta);
	this->tagEditorRect.setOutlineColor(sf::Color::Black);
	this->tagEditorRect.setOutlineThickness(1.f);
	this->isScrollHeld = false;
	this->maxTagsInPage = maxTagsPerPage;

	this->tagBoxSize = tagBoxSize;
	std::vector<std::string> tags = LoadFromFile();
	int noOfTags = tags.size();

	this->scrollBarRect.setSize(sf::Vector2f(15, tagEditorRect.getSize().y ));
	this->scrollBarRect.setPosition(sf::Vector2f(position.x + tagBoxSize.x, position.y));
	this->scrollRect.setPosition(this->scrollBarRect.getPosition());
	this->scrollBarRect.setFillColor(sf::Color::Black);
	this->scrollRect.setFillColor(sf::Color::Red);
	if (noOfTags > 0)
	{
		tagTextBoxes.resize(0);
		this->tags.resize(0);
		for (int i = 0; i < noOfTags; i++)
		{
			tagTextBoxes.push_back(new GUI::TextBox(position + Vector::Up * ((i)* tagBoxSize.y), sf::Vector2f(tagEditorRect.getSize().x, tagBoxSize.y), sf::Color::Black, sf::Color::White, sf::Color::Black, tags[i]));
			this->tags.push_back(tags[i]);
		}
	}
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	buttons["Save"] = new GUI::Button(sf::Vector2f(1730, 200), sf::Vector2f(60, 35), &this->font, "Save", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Add"] = new GUI::Button(sf::Vector2f(1730, 300), sf::Vector2f(60, 35), &this->font, "Add", sf::Color::White, sf::Color::Cyan, sf::Color::Red);
	buttons["Remove"] = new GUI::Button(sf::Vector2f(1730, 370), sf::Vector2f(60, 35), &this->font, "Remove", sf::Color::White, sf::Color::Cyan, sf::Color::Red);

	this->normalView.setSize(sf::Vector2f(1920, 1080));
	this->normalView.setCenter(this->normalView.getSize() / 2.f);
	sf::Vector2f tagPanelSize = tagEditorRect.getSize();
	this->scrollView.setSize(tagPanelSize);

	tagPanelSize.x /= 2.0;
	tagPanelSize.y /= 2.0;
	this->scrollView.setCenter(tagEditorRect.getPosition() + tagPanelSize);
	
	sf::Vector2f viewPort = tagEditorRect.getSize();
	viewPort.x /= 1920;
	viewPort.y /= 1080;
	this->scrollView.setViewport(sf::FloatRect((tagEditorRect.getPosition().x) / 1920, tagEditorRect.getPosition().y / 1080, viewPort.x, viewPort.y));
	this->isScrollBarVisible = false;
	//this->mainView.setCenter(position + Vector::Up * (tagEditorRect.getSize().y / 2));
	//this->mainView.setSize(tagCanvasSize);
	//this->mainView.setViewport(sf::FloatRect(position.x/1920,position.y/1080, tagCanvasSize.x / 1920, tagCanvasSize.y / 1080));

}

void TagEditor::Update()
{
	for (auto i : buttons)
		i.second->Update(InputDevices::Mouse::GetMousePosWindowf());
	for (auto* i : tagTextBoxes)
		i->Update();

	this->Input();
}

void TagEditor::Render(sf::RenderTarget* target)
{
	target->draw(tagEditorRect);
	target->setView(scrollView);
	for (auto* i : tagTextBoxes)
		i->Render(target);
	target->setView(normalView);

	for (auto i : buttons)
		i.second->Render(target);
	if (isScrollBarVisible)
	{
		target->draw(scrollBarRect);
		target->draw(scrollRect);
	}
}

const std::vector<std::string> TagEditor::GetTagStrings() const
{
	return this->tags;
}

void TagEditor::Input()
{
	
	currentHeightRatio = static_cast<float>( maxTagsInPage )/ tagTextBoxes.size();
	if (currentHeightRatio < 1)
	{

		this->isScrollBarVisible = true;
		scrollRect.setSize(sf::Vector2f(scrollBarRect.getSize().x, scrollBarRect.getSize().y * currentHeightRatio));
	}
	else
		this->isScrollBarVisible = false;
	if (this->isScrollBarVisible)
	{

		if (InputDevices::Mouse::GetMouseKeyPress(sf::Mouse::Left))
		{
			if (this->scrollRect.getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
			{
				this->isScrollHeld = true;
			}
		}
		else
			isScrollHeld = false;
	
	
		if (this->isScrollHeld)
		{
			// bounds for the rectscroll bar 
			float mouseDeltaY = InputDevices::Mouse::GetMouseDelta().y;
			scrollRect.move(sf::Vector2f(0, mouseDeltaY));
			sf::Vector2f position = scrollRect.getPosition();

			scrollView.move(sf::Vector2f(0, mouseDeltaY));
			sf::Vector2f scrollViewCenter = scrollView.getCenter();
			
			scrollViewCenter.y = Clamp(scrollViewCenter.y, tagEditorRect.getPosition().y + tagEditorRect.getSize().y / 2, tagEditorRect.getPosition().y + tagEditorRect.getSize().y / 2 + (tagTextBoxes.size() - maxTagsInPage) * tagBoxSize.y);
			scrollView.setCenter(scrollViewCenter);
			//std::cout << scrollView.getCenter().y << std::endl;

			position.y = Clamp(position.y, scrollBarRect.getPosition().y, scrollBarRect.getPosition().y + (scrollBarRect.getSize().y * (1 - currentHeightRatio)));
			scrollRect.setPosition(position);


		}
		sf::Vector2f position = scrollRect.getPosition();
		position.y = Clamp(position.y, scrollBarRect.getPosition().y, scrollBarRect.getPosition().y + (scrollBarRect.getSize().y * (1 - currentHeightRatio)));
		scrollRect.setPosition(position);

	}
	
	
	if (this->buttons["Save"]->IsPressed())
	{
		this->SaveToFile();
		
		this->tags.resize(tagTextBoxes.size());
		for (int i = 0; i < tagTextBoxes.size(); i++)
		{
			this->tags[i] = tagTextBoxes[i]->GetText();
		}
		//this->tileEditorTools->UpdateTags(this->GetTagStrings());
		this->tileLayerSelector->UpdateTags(this->GetTagStrings());
	}
	if (this->buttons["Add"]->IsPressed())
	{
		
		this->tagTextBoxes.push_back(new GUI::TextBox(tagEditorRect.getPosition() + Vector::Up * ((tagTextBoxes.size()) * this->tagBoxSize.y), sf::Vector2f(tagEditorRect.getSize().x, this->tagBoxSize.y), sf::Color::Black, sf::Color::White, sf::Color::Black, "Empty"));
	
	}
	if (this->buttons["Remove"]->IsPressed())
	{
	
		this->tagTextBoxes.pop_back();
	}

}

void TagEditor::SaveToFile()
{

	std::ofstream outputStream;
	std::string filePath = "../" + TagFile;
	outputStream.open(filePath);
	if (outputStream.is_open())
	{
		for (auto& i : tagTextBoxes)
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

float TagEditor::Clamp(float value, float min, float max)
{
	return(value <= min ? min : value >= max ? max : value);
}
