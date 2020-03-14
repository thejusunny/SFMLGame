#include "TextBox.h"
sf::RenderWindow *TextBox::window;
void TextBox::PollTextInput()
{

	sf::Event sfEvent;
	while (this->window->pollEvent(sfEvent))
	{
		if(sfEvent.type == sf::Event::TextEntered)
		{
			stringText += sfEvent.text.unicode;
	

		}
	
	}

}

bool TextBox::IsTextInBounds()
{
	return (this->text.findCharacterPos(cursorIndex - 1).x < this->textRectShape.getPosition().x + this->textRectShape.getGlobalBounds().width - 12);
}

TextBox::TextBox(sf::Vector2f position,sf::Vector2f textRectSize, sf::Color textColor ,sf::Color backFillColor, sf::Color borderColor, std::string defaultText)
{
	if (!this->font.loadFromFile("../Dosis-Light.ttf"))
	{
		std::cout << "Error";
	}
	this->fontSize = 24;
	this->cursorIndex = 0;
	this->deleteFreq = 0.15;
	this-> isSelectionActive = false;
	this->textRectShape.setSize(textRectSize);
	this->textRectShape.setFillColor(backFillColor);
	this->textColor = textColor;
	this->text.setFont(this->font);
	this->text.setFillColor(this->textColor);
	this->text.setString(defaultText);
	this->characterWidthOffset = (fontSize/2)+this->text.getLetterSpacing(); // with the letterspacing
	this->text.setCharacterSize(this->fontSize);
	this->textRectShape.setOutlineColor(borderColor);
	this->textRectShape.setOutlineThickness(1.f);
	this->textRectShape.setPosition(position);
	this->text.setPosition(this->textRectShape.getPosition().x , this->textRectShape.getPosition().y+10.f + this->text.getGlobalBounds().height / 2.f);
	this->cursor.setSize(sf::Vector2f(1, this->textRectShape.getSize().y - 6));
	this->cursor.setFillColor(sf::Color::Black);
	this->cursor.setPosition((this->textRectShape.getPosition().x+ this->cursorIndex*this->characterWidthOffset),this->textRectShape.getPosition().y+3);
	std::cout <<"Letter spacing:"<< this->text.getLetterSpacing() << std::endl;
	//this->cursor.setOutlineThickness(1.f);
	//this->cursor.setOutlineColor(sf::Color::Blue);
}

void TextBox::Update()
{
	if (Mouse::GetMouseKeyDown(sf::Mouse::Left))
	{
		
	
		if (this->textRectShape.getGlobalBounds().contains(Mouse::GetMousePosWindowf()))
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
	if (Keyboard::IsKeyPressed(sf::Keyboard::BackSpace)&&Time::time >timer+deleteFreq)
	{
	
		unsigned count = stringText.length();
		this->stringText = this->stringText.substr(0, count-1);
		--cursorIndex;
		if (this->IsTextInBounds())
		{
			this->text.setString(stringText);
			this->cursor.setPosition(this->text.findCharacterPos(cursorIndex).x, this->textRectShape.getPosition().y + 3);
		}
		timer = Time::time;

	}

	
}

void TextBox::Render(sf::RenderTarget* target)
{
	target->draw(this->textRectShape);
	target->draw(this->text);
	target->draw(this->cursor);

}

void TextBox::SetWindow(sf::RenderWindow *win)
{

	window = win;
}
