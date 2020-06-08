#include "GUI.h"

void GUI::Button::UpdateTextAnchors()
{
	this->text.setPosition(this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - 3 - this->text.getGlobalBounds().height / 2.f);
}

void GUI::Button::SetButtonText(std::string text)
{
	this->text.setString(text);
	this->text.setPosition(this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f)-3 - this->text.getGlobalBounds().height / 2.f);

}

std::string GUI::Button::GetButtonText() const
{
	return this->text.getString();
}

void GUI::Button::SetPosition(sf::Vector2f pos)
{
	buttonShape.setPosition(pos);
	UpdateTextAnchors();
}

void GUI::Button::SetActive(bool state) 
{
	this->isActive = state;
}

/*Button */
GUI::Button::Button(sf::Vector2f position, sf::Vector2f buttonSize, sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color clickColor,int fontSize,sf::Texture *tex)
{
	this->isActive = true;
	this->enabled = true;
	this->buttonTexture = tex;
	this->buttonPressDeltaTime = 0.15f;
	this->buttonShape.setPosition(position);
	this->buttonShape.setSize(buttonSize);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(fontSize);
	this->buttonState = ButtonState::IDLE;
	this->disabledColor = sf::Color(255, 0, 0);
	this->UpdateTextAnchors();
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressColor = clickColor;
	this->buttonShape.setFillColor(idleColor);
	this->buttonShape.setTexture(buttonTexture);
	this->buttonShape.setOutlineThickness(1.0);
	this->buttonShape.setOutlineColor(sf::Color::White);
}

void GUI::Button::Render(sf::RenderTarget* target)
{
	if (this->isActive)
	{
		target->draw(this->buttonShape);
		target->draw(this->text);
	}
}

void GUI::Button::Update(const sf::Vector2f mousePosition)
{

	if (this->isActive)
	{
		
		if (this->enabled)
		{

			this->buttonState = ButtonState::IDLE;
			if (this->buttonShape.getGlobalBounds().contains(mousePosition))
			{

				this->buttonState = ButtonState::HOVER;
				if (InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Left) && Time::time > lastPressTime + buttonPressDeltaTime)
				{
					this->buttonState = ButtonState::PRESSED;
					this->lastPressTime = Time::time;
				}

			}
			switch (buttonState)
			{
			case ButtonState::IDLE:
				this->buttonShape.setFillColor(idleColor);
				break;
			case ButtonState::HOVER:
				this->buttonShape.setFillColor(hoverColor);
				break;
			case ButtonState::PRESSED:
				this->buttonShape.setFillColor(pressColor);
				break;
			default:
				break;
			}
		}
		else
			this->buttonShape.setFillColor(disabledColor);
	}
		
}


const bool GUI::Button::IsPressed() const
{

	if (buttonState == ButtonState::PRESSED)
		return true;
	return false;
}

void GUI::Button::SetEnabled(bool state)
{
	this->enabled = state;
	buttonState = this->enabled ? buttonState : ButtonState::DISABLED;
}

auto GUI::Button::GetRect()
{
	return this->buttonShape.getGlobalBounds();
}


//TextBox
#include "Game.h"

sf::RenderWindow* GUI::TextBox::window;


bool  GUI::TextBox::IsTextInBounds()
{
	return (this->text.findCharacterPos(cursorIndex - 1).x < this->textRectShape.getPosition().x + this->textRectShape.getGlobalBounds().width - 12);
}

void GUI::TextBox::UpdateCursor()
{
	if (cursorIndex <= 0)
	{
		this->cursor.setPosition(this->textRectShape.getPosition().x, this->textRectShape.getPosition().y+1);
		return;
	}
	
	this->cursor.setPosition(this->text.findCharacterPos(cursorIndex).x, this->textRectShape.getPosition().y + 1);
}

const std::string GUI::TextBox::GetText() const
{
	return this->text.getString();
}

void GUI::TextBox::SetText(std::string str)
{
	this->text.setString(str);
	
}

GUI::TextBox::TextBox(sf::Vector2f position, sf::Vector2f textRectSize, sf::Color textColor, sf::Color backFillColor, sf::Color borderColor, std::string defaultText)
{
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	this->fontSize = 18;
	this->cursorIndex = 0;
	this->deleteFreq = 0.1;
	this->isSelectionActive = false;
	this->textRectShape.setSize(textRectSize);
	this->textRectShape.setFillColor(backFillColor);
	this->textColor = textColor;
	this->text.setFont(this->font);
	this->text.setFillColor(this->textColor);
	this->text.setString(defaultText);
	if(defaultText.length()<=1)
	this->text.setString("");
	this->stringText = text.getString();
	this->cursorIndex = text.getString().getSize();
	this->characterWidthOffset = (fontSize / 2) + this->text.getLetterSpacing(); // with the letterspacing
	this->text.setCharacterSize(this->fontSize);
	this->textRectShape.setOutlineColor(borderColor);
	this->textRectShape.setOutlineThickness(1.f);
	this->textRectShape.setPosition(position);
	float height = this->text.getLocalBounds().height;
	this->text.setPosition(this->textRectShape.getPosition().x, (this->textRectShape.getPosition().y  + ((this->textRectShape.getSize().y - this->text.getLocalBounds().height)/2)-1 ));
	this->cursor.setSize(sf::Vector2f(1, this->textRectShape.getSize().y-2));
	this->cursor.setFillColor(sf::Color::Black);
	this->UpdateCursor();
	//this->cursor.setPosition((this->textRectShape.getPosition().x + this->cursorIndex * this->characterWidthOffset), this->textRectShape.getPosition().y + 1);
	std::cout << "Letter spacing:" << this->text.getLetterSpacing() << std::endl;
	//this->cursor.setOutlineThickness(1.f);
	//this->cursor.setOutlineColor(sf::Color::Blue);
}

void  GUI::TextBox::Update()
{
	
	
	if (InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Left))
	{


		if (this->textRectShape.getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
		{
			this->isSelectionActive = true;
			if (cursorIndex >= 0)
			{
				std::cout << InputDevices::Mouse::GetMousePosWindowf().x;
				float startPositionX = this->textRectShape.getPosition().x;
				float mousePosX = InputDevices::Mouse::GetMousePosWindowf().x;
				int targetIndex = 0;
				for (int i = 0; i <= stringText.length(); i++)
				{
					if (mousePosX >= this->text.findCharacterPos(i).x-0.1f)
						targetIndex = i;
				}
			

				if (targetIndex <= stringText.length()+1)
				{
					cursorIndex = targetIndex;
					this->UpdateCursor();
				}

			}
			
		}
		else
			isSelectionActive = false;

	}
	if (isSelectionActive)
	{
		std::string inputChar = Game::GetInputChar();
		if (inputChar != "")
		{

			this->stringText.insert(cursorIndex,inputChar);
			//this->stringText += inputChar;
			this->cursorIndex++;
			if (this->IsTextInBounds())
			{
				this->text.setString(stringText);
				this->UpdateCursor();
			}

		}
		this->textRectShape.setOutlineColor(sf::Color(255, 0, 0, 255));

		if (InputDevices::Keyboard::IsKeyPressed(sf::Keyboard::BackSpace) && Time::time > timer + deleteFreq)
		{


			if (cursorIndex > 0)
			{
				unsigned count = stringText.length();
				this->stringText = this->stringText.substr(0, count - 1);
				--cursorIndex;
				if (this->IsTextInBounds())
				{
					this->text.setString(stringText);
					this->cursor.setPosition(this->text.findCharacterPos(cursorIndex).x, this->textRectShape.getPosition().y + 3);
				}
				timer = Time::time;
			}
		}

	}
	else
	{
		this->textRectShape.setOutlineColor(sf::Color::Black);
	}
	


}

void  GUI::TextBox::Render(sf::RenderTarget* target)
{
	target->draw(this->textRectShape);
	target->draw(this->text);
	target->draw(this->cursor);

}

void  GUI::TextBox::SetWindow(sf::RenderWindow* win)
{

	window = win;
}

GUI::DropDownBox::DropDownBox(std::vector<std::string> optionStrings,sf::Vector2f size, sf::Vector2f postion,bool useSearchBox)
{
	this->currentSelectedIndex = 0;
	this->isExpanded = false;
	this->optionSize = size;
	this->noOfVisibleButtons = 4;
	this->isScrollHeld = false;
	if (useSearchBox)
	{
		startOffset.y = size.y;
		searchBox = new TextBox(postion+startOffset, sf::Vector2f(size.x, size.y), sf::Color::Red, sf::Color::White, sf::Color::Black);
		

	}
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	this->searchOptions.resize(optionStrings.size());
	//TODO
	// the first one is always supposed to be enter box not included in the list

	this->optionStartPos = postion + startOffset + sf::Vector2f(0, size.y);
	this->dropDownRect.setPosition(optionStartPos);
	this->dropDownRect.setSize(sf::Vector2f(size.x, size.y * noOfVisibleButtons ));
	this->dropDownRect.setFillColor(sf::Color(128, 128, 128));
	this->scrollBarRect.setSize(sf::Vector2f(15, dropDownRect.getSize().y+size.y+startOffset.y));
	this->scrollBarRect.setPosition(sf::Vector2f(postion.x + size.x, postion.y));
	this->scrollRect.setPosition(this->scrollBarRect.getPosition());
	this->scrollBarRect.setFillColor(sf::Color::Black);
	this->scrollRect.setFillColor(sf::Color::Red);
	selectedButton =  new Button(postion, size, &this->font, "Empty", sf::Color::White, sf::Color::Blue, sf::Color::Red);
	selectedButton->SetActive(true);
	options.resize(optionStrings.size());
	for (int i = 0; i < optionStrings.size(); i++)
	{
		this->options[i] = new Button(startOffset+ sf::Vector2f(postion.x,postion.y+((i+1)*size.y)), size- (Vector::Up), &this->font,optionStrings[i], sf::Color::White, sf::Color::Blue,sf::Color::Red);
	}

	this->currentHeightRatio = dropDownRect.getSize().y / options.size() + 1;
	this->normalView.setSize(sf::Vector2f(1920, 1080));
	this->normalView.setCenter(this->normalView.getSize()/ 2.f);
	sf::Vector2f dropDownSize = dropDownRect.getSize();
	this->scrollView.setSize(dropDownSize);

	dropDownSize.x /= 2.0;
	dropDownSize.y /= 2.0;
	this->scrollView.setCenter(dropDownRect.getPosition() + dropDownSize);
	this->scrollViewDefaultCenterPos = scrollView.getCenter();
	sf::Vector2f viewPort = dropDownRect.getSize();
	viewPort.x /= 1920;
	viewPort.y /= 1080;
	this->scrollView.setViewport(sf::FloatRect((dropDownRect.getPosition().x)/1920,dropDownRect.getPosition().y/1080, viewPort.x, viewPort.y));
	this->dropDownRect.setOutlineThickness(1.f);
	this->dropDownRect.setOutlineColor(sf::Color::Red);

	
}

void GUI::DropDownBox::Update()
{
	
	searchOptions.clear();
	this->optionChanged = false;
	std::string searchText = this->searchBox->GetText();
	if (searchText!=" ")
	{
		//Search algorithm

		
		isSearching = true;
		for (int i = 0; i < options.size(); i++)
		{
			std::string btn = options[i]->GetButtonText();
			if (strstr(btn.c_str(),searchText.c_str() ))
			{
				this->searchOptions.push_back(options[i]);
				
			}
		}
		for (int i = 0; i < this->searchOptions.size(); i++)
		{
			this->searchOptions[i]->SetPosition(sf::Vector2f(optionStartPos.x, optionStartPos.y + (i * optionSize.y)));
		}
		currentHeightRatio = static_cast<float>(noOfVisibleButtons) / searchOptions.size();
	}
	else
	{
		currentHeightRatio = static_cast<float>(noOfVisibleButtons) / options.size();
		isSearching = false;
	}
	if (currentHeightRatio < 1)
	{

		scrollRect.setSize(sf::Vector2f(scrollBarRect.getSize().x, scrollBarRect.getSize().y * currentHeightRatio));
		isScrollBarVisible = true;


	}
	else
		isScrollBarVisible = false;
	if (this->isScrollBarVisible)
	{

		if (InputDevices::Mouse::GetMouseKeyPress(sf::Mouse::Left))
		{
			if (this->scrollBarRect.getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
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
			sf::Vector2f scrollViewCenter= scrollView.getCenter();
			if(isSearching)
				scrollViewCenter.y = Clamp(scrollViewCenter.y, dropDownRect.getPosition().y + dropDownRect.getSize().y / 2, dropDownRect.getPosition().y + dropDownRect.getSize().y / 2 + (searchOptions.size() - noOfVisibleButtons) * optionSize.y);
			else
			scrollViewCenter.y = Clamp(scrollViewCenter.y, dropDownRect.getPosition().y+ dropDownRect.getSize().y/2, dropDownRect.getPosition().y+ dropDownRect.getSize().y / 2+ (options.size()-noOfVisibleButtons)* optionSize.y);
			scrollView.setCenter(scrollViewCenter);
			//std::cout << scrollView.getCenter().y << std::endl;

			position.y = Clamp(position.y, scrollBarRect.getPosition().y, scrollBarRect.getPosition().y+(scrollBarRect.getSize().y*(1-currentHeightRatio)));
			scrollRect.setPosition(position);
		
			
		}

	
	}
	this->selectedButton->Update(InputDevices::Mouse::GetMousePosWindowf());
	if (this->selectedButton->IsPressed())
	{
		this->isExpanded = !isExpanded;
		std::cout << "pressed\n";

	}

	
	if(this->isExpanded)
	{
		
		if (this->searchBox!= NULL)
		this->searchBox->Update();
		sf::FloatRect viewRect(scrollView.getCenter() - scrollView.getSize() / 2.f, scrollView.getSize());
		if (isSearching)
		{
			if (!isScrollBarVisible)
			{
			
				
				this->scrollView.setCenter(this->scrollViewDefaultCenterPos);
			}
			for (int i = 0; i < searchOptions.size(); i++)
			{
				if (viewRect.intersects(searchOptions[i]->GetRect()))
				{
					searchOptions[i]->Update(InputDevices::Mouse::GetMousePosView(&scrollView));
					if (searchOptions[i]->IsPressed())
					{

						this->selectedButton->SetButtonText(searchOptions[i]->GetButtonText());
						this->currentSelectedIndex = i;// useless stuff
						this->isExpanded = false;
						this->optionChanged = true;
						break;
					}

				}
			}

		}
		else
		{
			for (int i = 0; i < options.size(); i++)
			{
				//PROBLEM - options outside view fructum still gets selected check with  bounds to solve that

				

				if (viewRect.intersects(options[i]->GetRect()))
				{
					options[i]->Update(InputDevices::Mouse::GetMousePosView(&scrollView));
					if (options[i]->IsPressed())
					{

						this->selectedButton->SetButtonText(options[i]->GetButtonText());
						this->currentSelectedIndex = i; // kinda useless stuff
						this->isExpanded = false;
						this->optionChanged = true;
						break;
					}
				}



			}
		}
	}


}

const bool GUI::DropDownBox::IsChanged() const
{
	return this->optionChanged;
}

void GUI::DropDownBox::Render(sf::RenderTarget* target)
{
	
	
	if (this->isExpanded)
	{
		target->draw(this->dropDownRect);
		target->setView(this->scrollView);
		
		if (isSearching)
		{
			for (auto i : searchOptions)
				i->Render(target);
		}
		else
		{
			for (auto i : options)
				i->Render(target);
		}
		target->setView(this->normalView);
		target->draw(this->scrollBarRect);
		if (isScrollBarVisible)
			target->draw(this->scrollRect);
		if (this->searchBox != NULL)
			this->searchBox->Render(target);
		
	}
	target->setView(this->normalView);
	this->selectedButton->Render(target);


}

const std::string GUI::DropDownBox::GetCurrentSelectedString() const
{
	return this->selectedButton->GetButtonText();

}

const int GUI::DropDownBox::GetCurrentSelectedIndex() const
{
	return this->currentSelectedIndex;
}

const void GUI::DropDownBox::SetCurrentSelectedString(std::string str)
{
	
	if (str.size() <= 0)
	{
		currentSelectedIndex = -1;
		this->selectedButton->SetButtonText(" ");
		return;
	}
	
	
	for (int i = 0; i < options.size(); i++)
	{
		if (str.compare(options[i]->GetButtonText())==0)
		{
			currentSelectedIndex = i;
			this->selectedButton->SetButtonText(options[i]->GetButtonText());
		}
	
	}
}

void GUI::DropDownBox::UpdateOptions(std::vector<std::string> optionStrings)
{
	this->options.resize(optionStrings.size());
	for (int i = 0; i < optionStrings.size(); i++)
	{
		if (this->options[i] == NULL)
		{
			this->options[i] = new Button(this->optionStartPos+((float)i*optionSize), optionSize - (Vector::Up), &this->font, optionStrings[i], sf::Color::White, sf::Color::Blue, sf::Color::Red);
			
		}
		options[i]->SetButtonText(optionStrings[i]);
	}


	//auto it = this->options.begin() + optionStrings.size();
	//this->options.erase(it, this->options.end());
}

GUI::DropDownBox::~DropDownBox()
{
	delete selectedButton;
	for (auto i : options)
		delete i;
	delete searchBox;
}

float GUI::DropDownBox::Clamp(float value, float min, float max)
{
	
	return(value <= min ? min : value >= max ? max : value);

}


