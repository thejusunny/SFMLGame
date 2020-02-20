#include "Tile.h"
#include<iostream>
#include<stdlib.h>

Tile::Tile()
{
}
Tile::Tile(sf::Texture *texture, sf::Vector2u tilePosition, float gridSizeF)
{
	this->tileShape.setSize(sf::Vector2f( gridSizeF,gridSizeF));
	/*sf::Uint8 r=rand()/255;
	sf::Uint8 g=125;
	sf::Uint8 b=rand()/255;
	sf::Uint8 a=255;
	this->tileShape.setFillColor(sf::Color( r,g,b,a));*/
	this->tileShape.setTexture(texture);
	this->tileShape.setPosition(tilePosition.x,tilePosition.y);
}

Tile::~Tile()
{
}

void Tile::Render(sf::RenderTarget& target)
{
	
	target.draw(tileShape);
}

void Tile::SetTexture(sf::Texture* texture)
{
	this->tileShape.setTexture(texture);
}
