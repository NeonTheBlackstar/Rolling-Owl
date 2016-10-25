#include "Header.h"

Player::Player(float _x, float _y, int rad, float boun, sf::Vector2f acc, std::string _texture)
	: Moveable(boun, acc), canJump(false), Circle(_x, _y, rad, _texture)
{
	jumpHeight = 0.2;
	enableCollisions = true;
}

void Player::update(Game * pGame)
{
	horizontalMov(pGame);
	verticalMov(pGame);
}

void Player::horizontalMov(Game * pGame)
{
	/// Calculating horizontal movement vector: speed
	float delta = pGame->delta;
	float acc = delta * v_acceleration.x;
	float gameSpeed = pGame->gameSpeed; /// Maximum speed

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (v_speed.x > 0)
			v_speed.x -= acc * 3; /// Changing direction will be faster
		else
			v_speed.x -= acc;

		if (v_speed.x < -delta*gameSpeed)
			v_speed.x = -delta*gameSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (v_speed.x < 0)
			v_speed.x += acc * 3; /// Changing direction will be faster
		else
			v_speed.x += acc;

		if (v_speed.x > delta*gameSpeed)
			v_speed.x = delta*gameSpeed;
	}
	else /// Plynne hamowanie, trzeba to zast¹piæ tarciem!
	{
		if (v_speed.x < 0)
		{
			v_speed.x += acc;
			if (v_speed.x > 0)
				v_speed.x = 0;
		}
		else if (v_speed.x > 0)
		{
			v_speed.x -= acc;
			if (v_speed.x < 0)
				v_speed.x = 0;
		}
	}

	move(v_speed.x, 0);
	rotate(v_speed.x);

	x = getPosition().x;
}

void Player::verticalMov(Game * pGame)
{
	float delta = pGame->delta;
	float acc = delta * v_acceleration.x;
	float gameSpeed = pGame->gameSpeed; /// Maximum speed
										/// Calculating vertical movement vector: jump

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (v_speed.y > 0)
			v_speed.y -= acc * 3; /// Changing direction will be faster
		else
			v_speed.y -= acc;

		if (v_speed.y < -delta*gameSpeed)
			v_speed.y = -delta*gameSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (v_speed.y < 0)
			v_speed.y += acc * 3; /// Changing direction will be faster
		else
			v_speed.y += acc;

		if (v_speed.y > delta*gameSpeed)
			v_speed.y = delta*gameSpeed;
	}
	else /// Plynne hamowanie, trzeba to zast¹piæ tarciem!
	{
		if (v_speed.y < 0)
		{
			v_speed.y += acc;
			if (v_speed.y > 0)
				v_speed.y = 0;
		}
		else if (v_speed.y > 0)
		{
			v_speed.y -= acc;
			if (v_speed.y < 0)
				v_speed.y = 0;
		}
	}


	move(0, v_speed.y);

	y = getPosition().y;
}

void Player::onCollision(sf::Vector2f v_interPoint)
{
	Moveable::onCollision(v_interPoint, objectInfo(), this);
}
