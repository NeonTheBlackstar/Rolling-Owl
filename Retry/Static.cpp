
#include "Header.h"

Static::Static(float _x, float _y, sf::Vector2f _size, std::string _texture)
	: Rectangle(_x, _y, _size, _texture)
{
	isStatic = true;
}

void Static::update(Game * pGame)
{

}