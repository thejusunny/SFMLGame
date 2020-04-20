#include "GUI.h"

void GUI::Button::SetButtonText(std::string text)
{
	this->text.setString(text);
	this->text.setPosition(this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f)-3 - this->text.getGlobalBounds().height / 2.f);

}

const std::string GUI::Button::GetButtonText() const
{
	return this->text.getString();
}

void GUI::Button::SetActive(bool state)
{
	this->isActive = state;
}

/*Button */
GUI::Button::Button(sf::Vector2f position, sf::Vector2f buttonSize, sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color clickColor,int fontSize)
{
	this->isActive = true;
	this->enabled = true;
	this->buttonPressDeltaTime = 0.1f;
	this->buttonShape.setPosition(position);
	this->buttonShape.setSize(buttonSize);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(fontSize);
	this->buttonState = ButtonState::IDLE;
	this->disabledColor = sf::Color(255, 0, 0);
	this->text.setPosition(this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f)-3 - this->text.getGlobalBounds().height / 2.f);
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressColor = clickColor;
	this->buttonShape.setFillColor(idleColor);
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


//TextBox
#include "Game.h"

sf::RenderWindow* GUI::TextBox::window;


bool  GUI::TextBox::IsTextInBounds()
{
	return (this->text.findCharacterPos(cursorIndex - 1).x < this->textRectShape.getPosition().x + this->textRectShape.getGlobalBounds().width - 12);
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
	this->characterWidthOffset = (fontSize / 2) + this->text.getLetterSpacing(); // with the letterspacing
	this->text.setCharacterSize(this->fontSize);
	this->textRectShape.setOutlineColor(borderColor);
	this->textRectShape.setOutlineThickness(1.f);
	this->textRectShape.setPosition(position);
	this->text.setPosition(this->textRectShape.getPosition().x, this->textRectShape.getPosition().y + 3 + this->text.getGlobalBounds().height / 2.f);
	this->cursor.setSize(sf::Vector2f(1, this->textRectShape.getSize().y - 7));
	this->cursor.setFillColor(sf::Color::Black);
	this->cursor.setPosition((this->textRectShape.getPosition().x + this->cursorIndex * this->characterWidthOffset), this->textRectShape.getPosition().y + 1);
	std::cout << "Letter spacing:" << this->text.getLetterSpacing() << std::endl;
	//this->cursor.setOutlineThickness(1.f);
	//this->cursor.setOutlineColor(sf::Color::Blue);
}

void  GUI::TextBox::Update()
{
	if (InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Left))
	{


		if (this->textRectShape.getGlobalBounds().contains(InputDevices::Mouse::GetMousePosWindowf()))
			this->isSelectionActive = true;
		else
			isSelectionActive = false;

	}
	if (isSelectionActive)
	{
		std::string inputChar = Game::GetInputChar();
		if (inputChar != "")
		{

			this->stringText += inputChar;
			this->cursorIndex++;
			if (this->IsTextInBounds())
			{
				this->text.setString(stringText);
				this->cursor.setPosition(this->text.findCharacterPos(cursorIndex).x, this->textRectShape.getPosition().y + 3);
			}

		}
		this->textRectShape.setOutlineColor(sf::Color(255, 0, 0, 255));

	}
	else
		this->textRectShape.setOutlineColor(sf::Color::Black);
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

GUI::DropDownBox::DropDownBox(std::vector<std::string> optionStrings,sf::Vector2f size, sf::Vector2f postion)
{
	this->currentSelectedIndex = 0;
	this->isExpanded = false;
	this->optionSize = size;
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	//TODO
	// the first one is always supposed to be enter box not included in the list
	
	selectedButton =  new Button(sf::Vector2f(postion.x, postion.y), size, &this->font, "Empty", sf::Color::White, sf::Color::Blue, sf::Color::Red);
	selectedButton->SetActive(true);
	options.resize(optionStrings.size());
	for (int i = 0; i < optionStrings.size(); i++)
	{
		this->options[i] = new Button(sf::Vector2f(postion.x,postion.y+((i+1)*size.y)), size, &this->font,optionStrings[i], sf::Color::White, sf::Color::Blue,sf::Color::Red);
	}

	this->dropDownRect.setPosition(postion);
	this->dropDownRect.setSize(sf::Vector2f( size.x, size.y * optionStrings.size()));

	
}

void GUI::DropDownBox::Update()
{
	this->selectedButton->Update(InputDevices::Mouse::GetMousePosWindowf());
	if (this->selectedButton->IsPressed())
	{
		this->isExpanded = !isExpanded;
		std::cout << "pressed\n";

	}
	
	if(this->isExpanded)
	{
	

		for (int i=0;i<options.size();i++)
		{
			
			options[i]->Update(InputDevices::Mouse::GetMousePosWindowf());
			if (options[i]->IsPressed())
			{
				
				this->selectedButton->SetButtonText(options[i]->GetButtonText());
				this->currentSelectedIndex = i;
				this->isExpanded = false;
			}
		
		}
	}


}

void GUI::DropDownBox::Render(sf::RenderTarget* target)
{
	if (this->isExpanded)
	{
		target->draw(this->dropDownRect);
		this->selectedButton->Render(target);
		for (auto i : options)
			i->Render(target);
	}
	else
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

GUI::DropDownBox::~DropDownBox()
{
	delete selectedButton;
	for (auto i : options)
		delete i;
}

