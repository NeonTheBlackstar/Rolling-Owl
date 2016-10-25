#include "Header.h"

Circle::Circle(float _x, float _y, int rad, std::string _texture)
	: sf::CircleShape(rad), Entity(_texture), radius(rad), x(_x), y(_y)
{
	setOrigin(rad, rad);
	setPosition(_x, _y);
	setTexture(&texture);
}

Circle::~Circle() {}

void Circle::drawShape(Game * pGame)
{
	sf::CircleShape * pBase = this;
	pGame -> draw(*pBase);
}

std::string Circle::shapeName()
{
	return "Circle";
}

t_info Circle::objectInfo()
{
	t_info v_info;
	v_info.push_back(sf::Vector2f(getPosition().x, getPosition().y)); /// Coordinates of center of object
	v_info.push_back(sf::Vector2f(radius, radius)); /// Radius of sphere in each value
	return v_info;
}