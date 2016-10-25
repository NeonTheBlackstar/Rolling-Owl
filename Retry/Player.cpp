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
	float delta = pGame -> delta;
	float acc = delta * v_acceleration.x;
	float gameSpeed = pGame -> gameSpeed; /// Maximum speed

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
	else /// Plynne hamowanie
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
	/// Horizontal collisions with window
	if (v_speed.x + getPosition().x < 0 + radius)
	{
		v_speed.x = -v_speed.x * bounacy;
		if (abs(v_speed.x) < abs(delta))
			setPosition(0 + radius, getPosition().y);
	}
	else if (v_speed.x + getPosition().x > pGame -> videoX - radius)
	{
		v_speed.x = -v_speed.x * bounacy;
		if (abs(v_speed.x) < abs(delta))
			setPosition(pGame->videoX - radius, getPosition().y);
	}

	move(v_speed.x, 0);
	rotate(v_speed.x);

	x = getPosition().x;
}

void Player::verticalMov(Game * pGame)
{
	float delta = pGame->delta;
	float gravity = gravityAcc(delta, pGame->gravity);
	/// Calculating vertical movement vector: jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump == true) /// zamien nazwe na onGround lub inAir
	{
		v_speed.y = jumpHeight;
		canJump = false;
	}
	else if (canJump == false)
	{
		v_speed.y += gravity;
		/// Detect collision with ground
		if (getPosition().y + v_speed.y >= (pGame -> videoY) - radius)
		{
			v_speed.y = -v_speed.y * bounacy;
			if (abs(v_speed.y) < abs(delta))
			{
				v_speed.y = 0;
				setPosition(getPosition().x, (pGame -> videoY) - radius);
				canJump = true;
			}
		}
	}
	move(0, v_speed.y);

	y = getPosition().x;
}

void Player::onCollision(sf::Vector2f v_interPoint)
{
	Moveable::onCollision(v_interPoint, objectInfo(), this);
}
