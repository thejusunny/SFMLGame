#pragma once
#include <SFML\Graphics.hpp>
#include<sstream>
#include<string.h>
enum  TileType
{
	Enemies,Walls,Door,Water,Mud
};

class Tile
{
private:
	sf::RectangleShape tileShape;
	int textureIndex;
	bool collision;
	sf::Texture* texture;
	//TileType tileType;
	std::string tileTag;
	int layerNo;
public:

	Tile(sf::Texture *texture,int layerNo,sf::Vector2u tilePosition,float gridSizeF, int textureIndex,bool collision,std::string tileTag="");
	Tile(sf::Texture* texture, sf::Vector2u tilePosition, float gridSizeF);
	~Tile();
	void Render(sf::RenderTarget& target);
	void SetTexture(sf::Texture *texture);
	sf::Texture* GetTexture();
	std::string GetTileInfoAsString();
	const sf::Vector2f GetPosition()const;
	const sf::RectangleShape* GetShape()const;
	const bool IsCollidable()const;
	void SetCollision(bool state);
	void SetTileTag(std::string tileTag);
	const std::string GetTileTag()const;
};



