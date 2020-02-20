#pragma once
#include <SFML\Graphics.hpp>
#include<iostream>
#include"Mouse.h"
enum ButtonState
{
	IDLE =0, HOVER, PRESSED
};
class Button
{
private:
	sf::RectangleShape buttonShape;
	sf::Font *font;
	sf::Text text;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressColor;
	short unsigned buttonState;
public :
	Button(sf::Vector2f position, sf::Vector2f buttonSize, sf::Font *font,std::string text, 
		sf::Color idleColor,sf::Color hoverColor,sf::Color clickColor);
	void Render(sf::RenderTarget* target);
	void Update(const sf::Vector2f mousePosition);
	const bool IsPressed()const;
};

