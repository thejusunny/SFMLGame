#pragma once

#include"InputDevices.h"
enum ButtonState
{
	IDLE = 0, HOVER, PRESSED
};
namespace GUI
{
	class Button
	{
	private:
		sf::RectangleShape buttonShape;
		sf::Font* font;
		sf::Text text;
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color pressColor;
		short unsigned buttonState;
	public:
		Button(sf::Vector2f position, sf::Vector2f buttonSize, sf::Font* font, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color clickColor);
		void Render(sf::RenderTarget* target);
		void Update(const sf::Vector2f mousePosition);
		const bool IsPressed()const;
	};

	class TextBox
	{
	private:
		sf::RectangleShape textRectShape;
		sf::Text text;
		sf::Color backFillColor;
		sf::Color textColor;
		static sf::RenderWindow* window;
		std::string stringText;
		void PollTextInput();
		bool isSelectionActive;
		sf::Font font;
		float deleteFreq;
		float timer;
		sf::RectangleShape cursor;
		int cursorIndex;
		float characterWidthOffset;
		int fontSize;
		bool IsTextInBounds();
	public:
		const std::string GetText()const;
		void SetText(std::string str);
		TextBox(sf::Vector2f position, sf::Vector2f textRectSize, sf::Color textColor, sf::Color backFillColor,
			sf::Color borderColor, std::string defaultText = " ");
		void Update();
		void Render(sf::RenderTarget* target);
		static void SetWindow(sf::RenderWindow* win);

	};
	class DropDownBox
	{
	public:
		std::vector<Button*> options;
	private:

		int currentSelectedIndex;
	};

}

