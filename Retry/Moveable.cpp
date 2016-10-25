#include "Header.h"

Moveable::Moveable(float b, sf::Vector2f acc)
	: bounacy(b)
{
	v_acceleration = acc;
}

Moveable::~Moveable() {}

/// Gravity values from 0 to 1
float Moveable::gravityAcc(float delta, float gravity)
{
	return delta * gravity;
}

void Moveable::onCollision(sf::Vector2f v_interPoint, t_info v_info, Player * pPlayer) /// Czy to nie powinno byc oddzielnie dla Rec i Circle?
{
	/// Computing line function parameters
	float a = angularCoefficient(&sf::Vector2f(0,0), &v_speed);
	float b, radius, toAdd, new_y, new_x;
	/// Handle exceptions
	if (a == 0)
	{
		if (v_speed.x == 0) /// nie powinienem wykrywac tego za pomoca wektora predkosci??? moze jednak jest ok?
		{ 
			//system("pause");
			new_x = v_info[0].x;
			toAdd = radius - abs(v_info[0].y - v_interPoint.y); /// wartosc bezwgledna czy nie?
			int direction = v_speed.y > 0 ? 1 : -1;
			new_y = v_info[0].y + toAdd*(-direction);

			pPlayer->setPosition(new_x, new_y);
		}
		else if (v_speed.y == 0)
		{
			new_y = v_info[0].y;
			toAdd = radius - abs(v_info[0].x - v_interPoint.x);
			int direction = v_speed.x > 0 ? 1 : -1;
			new_x = v_info[0].x + toAdd*(-direction);

			pPlayer->setPosition(new_x, new_y);
		}
	}
	else
	{
		/*b = absoluteTerm(a, &v_info[0]);
		/// Computing "y"
		radius = v_info[1].x;
		toAdd = radius - abs(v_info[0].y - v_interPoint.y);
		int direction = v_speed.x > 0 ? 1 : -1;
		new_y = v_info[0].y + toAdd*(-direction);
		new_x = (new_y - b) / a;*/
	}

	v_speed = -v_speed * bounacy; /// bedac na platformie przeciwdziala ruchowi w lewo lub w prawo. naprawic!
	/*
	v_speed = -v_speed * bounacy;

	if (abs(v_speed.x) < abs(delta))
		setPosition(0 + radius, getPosition().y);
	*/
}