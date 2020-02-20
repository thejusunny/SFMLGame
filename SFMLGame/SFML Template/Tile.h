#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
private:
	sf::RectangleShape tileShape;

public:
	Tile();
	Tile(sf::Texture *texture,sf::Vector2u tileSize,float gridSizeF);
	~Tile();
	void Render(sf::RenderTarget& target);
	void SetTexture(sf::Texture *texture);
};

