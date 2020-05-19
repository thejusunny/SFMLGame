#pragma once

#include"InputDevices.h"
#include <algorithm>
enum ButtonState
{
	IDLE = 0, HOVER, PRESSED ,TOGGLED,DISABLED
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
		sf::Color disabledColor;
		short unsigned buttonState;
		float buttonPressDeltaTime;
		float lastPressTime;
		bool isActive;
		bool enabled;
		sf::Texture *buttonTexture;
		void UpdateTextAnchors();
	public:
		void SetButtonText(std::string text);
		std::string GetButtonText()const;
		void SetPosition(sf::Vector2f pos);

		void SetActive(bool state);
		Button(sf::Vector2f position, sf::Vector2f buttonSize, sf::Font* font, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color clickColor, int fontSize = 18, sf::Texture * tex = nullptr);
		void Render(sf::RenderTarget* target);
		void Update(const sf::Vector2f mousePosition);
		const bool IsPressed()const;
		void SetEnabled(bool state);
		auto GetRect();
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
		bool isSelectionActive;
		sf::Font font;
		float deleteFreq;
		float timer;
		sf::RectangleShape cursor;
		int cursorIndex;
		float characterWidthOffset;
		int fontSize;
		bool IsTextInBounds();
		void UpdateCursor();
	public:
		const std::string GetText()const;
		void SetText(std::string str);
		TextBox(sf::Vector2f position, sf::Vector2f textRectSize, sf::Color textColor, sf::Color backFillColor,
			sf::Color borderColor, std::string defaultText = "A");
		void Update();
		void Render(sf::RenderTarget* target);
		static void SetWindow(sf::RenderWindow* win);
		

	};
	class DropDownBox
	{
	public:
		DropDownBox(std::vector<std::string> options, sf::Vector2f size, sf::Vector2f postion,bool useSearchBox= false);
		std::vector<Button*> options;
		std::vector<Button*> searchOptions;
		Button* selectedButton;
		sf::RectangleShape dropDownRect;
		void Update();
		void Render(sf::RenderTarget* target);
		const std::string GetCurrentSelectedString()const;
		const int GetCurrentSelectedIndex()const;
		~DropDownBox();
		float Clamp(float value, float max, float min);
	private:
		bool isSearching;
		TextBox* searchBox;
		sf::View scrollView;
		sf::View normalView;
		sf::RectangleShape scrollRect;
		sf::RectangleShape scrollBarRect;
		sf::Vector2f optionSize;
		bool isExpanded;
		sf::Font font;
		int currentSelectedIndex;
		sf::Vector2f startOffset;
		sf::Vector2f optionStartPos;
		float currentHeightRatio;
		int noOfVisibleButtons;
		bool isScrollBarVisible;
		bool isScrollHeld;
		
	};
	
}

