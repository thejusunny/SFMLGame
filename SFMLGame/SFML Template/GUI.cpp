#include "GUI.h"

/*Button */
GUI::Button::Button(sf::Vector2f position, sf::Vector2f buttonSize, sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color clickColor)
{
	this->buttonShape.setPosition(position);
	this->buttonShape.setSize(buttonSize);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(18);
	this->buttonState = ButtonState::IDLE;
	this->text.setPosition(this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressColor = clickColor;
	this->buttonShape.setFillColor(idleColor);
}

void GUI::Button::Render(sf::RenderTarget* target)
{

	target->draw(this->buttonShape);
	target->draw(this->text);
}

void GUI::Button::Update(const sf::Vector2f mousePosition)
{

	this->buttonState = ButtonState::IDLE;
	if (this->buttonShape.getGlobalBounds().contains(mousePosition))
	{

		this->buttonState = ButtonState::HOVER;
		if (InputDevices::Mouse::GetMouseKeyDown(sf::Mouse::Left))
		{
			this->buttonState = ButtonState::PRESSED;
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


const bool GUI::Button::IsPressed() const
{
	if (buttonState == ButtonState::PRESSED)
		return true;
	return false;
}


//TextBox
#include "Game.h"

sf::RenderWindow* GUI::TextBox::window;
void GUI::TextBox::PollTextInput()
{

	sf::Event sfEvent;
	while (this->window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::TextEntered)
		{
			stringText += sfEvent.text.unicode;


		}

	}

}

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
