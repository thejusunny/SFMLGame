#include "Tile.h"
#include<iostream>
#include<stdlib.h>


Tile::Tile(sf::Texture* texture, int layerNo,sf::Vector2u tilePosition, float gridSizeF, int textureIndex,bool collision=false,std::string tileTag)
{
	this->tileShape.setSize(sf::Vector2f( gridSizeF,gridSizeF));
	this->layerNo = layerNo;
	this->collision = collision;
	this->texture = texture;
	this->tileTag = tileTag;
	this->textureIndex = textureIndex;
	this->tileShape.setTexture(this->texture);
	this->tileShape.setPosition(tilePosition.x,tilePosition.y);
}

Tile::Tile(sf::Texture* texture, sf::Vector2u tilePosition, float gridSizeF)
{
	this->texture = texture;
	this->collision = false;
	this->tileShape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tileShape.setTexture(texture);
	this->tileShape.setPosition(tilePosition.x, tilePosition.y);

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

sf::Texture* Tile::GetTexture()
{
	return this->texture;
}

std::string Tile::GetTileInfoAsString()
{
	std::stringstream sStream;
	sStream <<this-> textureIndex << " " <<this-> collision << " "<<this->tileTag;
	return sStream.str();
}

const sf::Vector2f Tile::GetPosition() const
{
	return this->tileShape.getPosition();
}
const sf::RectangleShape* Tile::GetShape() const
{
	return &this->tileShape;
}

const bool Tile::IsCollidable() const
{

	return this->collision;
}

void Tile::SetCollision(bool state)
{
	this->collision = state;
}

void Tile::SetTileTag(std::string tileTag)
{
	this->tileTag = tileTag;
}

const std::string Tile::GetTileTag() const
{
	return this->tileTag;
}
