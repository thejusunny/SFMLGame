#pragma once
#include <SFML\Graphics.hpp>
#include<sstream>
class Tile
{
private:
	sf::RectangleShape tileShape;
	int textureIndex;
	bool collision;
	sf::Texture* texture;
public:

	Tile(sf::Texture *texture,sf::Vector2u tilePosition,float gridSizeF, int textureIndex);
	Tile(sf::Texture* texture, sf::Vector2u tilePosition, float gridSizeF);
	~Tile();
	void Render(sf::RenderTarget& target);
	void SetTexture(sf::Texture *texture);
	std::string GetTileInfoAsString();
};

