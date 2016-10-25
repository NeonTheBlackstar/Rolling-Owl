#include "Header.h"

Rectangle::Rectangle(float _x, float _y, sf::Vector2f _size, std::string _texture)
	: sf::RectangleShape(_size), Entity(_texture), width(_size.x), height(_size.y), x(_x), y(_y)
{
	setOrigin(_size.x / 2, _size.y / 2);
	setPosition(_x, _y);
	setTexture(&texture);
}

Rectangle::~Rectangle() {}

void Rectangle::drawShape(Game * pGame)
{
	sf::RectangleShape * pBase = this;
	pGame->draw(*pBase);
}

std::string Rectangle::shapeName()
{
	return "Rectangle";
}

t_info Rectangle::objectInfo()
{
	float vertex_X, vertex_Y;
	t_info v_info;
	v_info.push_back(sf::Vector2f(getPosition().x, getPosition().y)); /// Coordinates of center of object
	v_info.push_back(sf::Vector2f(width, height)); /// Width and height of rectangle

	/// Okreslam wektor przesuniecia na podstawie roznicy punktu centralnego przed przemieszczeniem w konstruktorze i po
	sf::Vector2f v_originCenter(width / 2.0, height / 2.0);
	sf::Vector2f v_translation = v_info.at(0) - v_originCenter;

	for (int i = 0; i < getPointCount(); ++i)
	{
		v_info.push_back( getPoint(i) + v_translation);
	}

	return v_info;
}