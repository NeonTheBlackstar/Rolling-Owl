#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <vector>
#include <map>

//### PROTOTYPES ###//

class World;
class Game;
class Entity;
class Player;
class Moveable;
class Circle;
class Rectangle;
class Static;

float distanceBetweenPoints(sf::Vector2f * v1, sf::Vector2f * v2);
float angularCoefficient(sf::Vector2f * v1, sf::Vector2f * v2);
float absoluteTerm(sf::Vector2f * v1, sf::Vector2f * v2);
float absoluteTerm(float a, sf::Vector2f * v);
bool isBetweenPoints(sf::Vector2f * point, sf::Vector2f * v1, sf::Vector2f * v2);

//### TYPES ###//

typedef std::vector< sf::Vector2f > t_info;
typedef std::vector< sf::Vector2f >::iterator it_info;
typedef std::vector<Entity*>::iterator it_entities;

//### CLASSES ###//

class World
{
public:
	float gravity;
	float gameSpeed;
	/// Zdefiniowac opor powietrza

	std::vector<Entity *> v_entities;

	void setUpWorld(float _grv, float _gmS);
	void loadEntityOnQueue(Entity * pE);
};

class Game : public sf::RenderWindow, public World
{
public:
	Game(int x, int y, std::string name);
	~Game();

	float videoX, videoY;
	sf::Clock clock;
	float delta;

	void MainLoop();
	void handleEvents();
	void drawEntities();
	float getDelta();

	/// Collision module

	void detectCollisions(it_entities i);
	bool CC_collision(t_info pC1, t_info pC2, sf::Vector2f &v_interPoint);
	bool CR_collision(t_info pC, t_info pR, sf::Vector2f &v_interPoint);
	bool RR_collision(t_info pR1, t_info pR2, sf::Vector2f &v_interPoint);
};

class Entity
{
public:
	Entity(std::string textureName);
	virtual ~Entity() = 0; /// so we can delete object from pointer to base class

	sf::Texture texture;
	bool enableCollisions;
	bool isStatic;

	virtual void update(Game * pGame);
	virtual void drawShape(Game * pGame);
	virtual std::string shapeName();
	virtual t_info objectInfo();
	virtual void onCollision(sf::Vector2f v_interPoint);
};

class Circle : public Entity, public sf::CircleShape
{
public:
	Circle(float _x, float _y, int rad, std::string _texture);
	~Circle();

	float radius;
	float x; /// po³¹czyæ w jednen wektor Postion / Coordinates
	float y;

	void drawShape(Game * pGame);
	std::string shapeName();
	t_info objectInfo();
};

class Rectangle : public Entity, public sf::RectangleShape
{
public:
	Rectangle(float _x, float _y, sf::Vector2f _size, std::string _texture);
	~Rectangle();

	float width;
	float height;
	float x;
	float y;

	void drawShape(Game * pGame);
	std::string shapeName();
	t_info objectInfo();
};

class Moveable
{
public:
	Moveable(float b, sf::Vector2f acc);
	virtual ~Moveable() = 0;

	float mass;		/// ogarnac
	float force;	/// ogarnac
	sf::Vector2f v_speed;
	sf::Vector2f v_acceleration;
	float bounacy;
	float jumpHeight;

	float gravityAcc(float delta, float gravity);
	void onCollision(sf::Vector2f v_interPoint, t_info v_info, Player * pPlayer);
};

class Player : public Circle, public Moveable
{
public:
	Player(float _x, float _y, int rad, float boun, sf::Vector2f acc, std::string _texture);

	bool canJump;

	void update(Game * pGame);
	void horizontalMov(Game * pGame);
	void verticalMov(Game * pGame);
	
	void onCollision(sf::Vector2f v_interPoint);
};

class Static : public Rectangle
{
public:
	Static(float _x, float _y, sf::Vector2f _size, std::string _texture);

	void update(Game * pGame);
};
