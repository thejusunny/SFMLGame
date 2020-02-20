#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f buttonSize, sf::Font* font, std::string text,
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

void Button::Render(sf::RenderTarget* target)
{

	target->draw(this->buttonShape);
	target->draw(this->text);
}

void Button::Update(const sf::Vector2f mousePosition)
{

	this->buttonState = ButtonState::IDLE;
	
	if (this->buttonShape.getGlobalBounds().contains(mousePosition))
	{
	
		this->buttonState = ButtonState::HOVER;
		if (Mouse::GetMouseKeyDown(sf::Mouse::Left))
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


const bool Button::IsPressed() const
{
	if (buttonState == ButtonState::PRESSED)
		return true;
	return false;
}

