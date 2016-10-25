#include "Header.h"

Game::Game(int x, int y, std::string name)
	: sf::RenderWindow(sf::VideoMode(x, y), name)
{
	videoX = x;
	videoY = y;

	sf::RenderTarget::initialize();
}
Game::~Game()
{
	for (std::vector<Entity*>::iterator i = v_entities.begin(); i != v_entities.end(); ++i)
		delete (*i);
}

void Game::MainLoop()
{
	while (sf::Window::isOpen())
	{
		getDelta();
		handleEvents();
		/// Draw objects ///
		clear();
		drawEntities();
		display();
	}
}

void Game::handleEvents()
{
	sf::Event event;
	while (pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			sf::Window::close();
			break;
		}
	}
}

void Game::drawEntities()
{
	//std::cout << "DRAW^^^^^^^^^^^^^^^^^^^^^\n";
	for (std::vector<Entity*>::iterator i = v_entities.begin(); i != v_entities.end(); ++i)
	{
		(*i)->update(this);
		//std::cout << "START------------------\n";
		detectCollisions(i);
		//std::cout << "END------------------\n";
		(*i)->drawShape(this);
	}
	//std::cout << "DRAW-END^^^^^^^^^^^^^^^^^^^^^\n";
	//system("pause");
}

float Game::getDelta()
{
	delta = clock.restart().asSeconds();
	return delta;
}

void Game::detectCollisions(it_entities i) /// With other objects
{
	std::string name1, name2;
	t_info m_info1;
	t_info m_info2;
	bool isCollision;
	sf::Vector2f v_intersectionPoint;

	for (std::vector<Entity*>::iterator k = i + 1; k != v_entities.end(); ++k)
	{
		isCollision = false;
		if ( (*i)->isStatic == true && (*k)->isStatic == true || (*i)->enableCollisions == false || (*k)->enableCollisions == false )
			continue;

		name1 = (*i)->shapeName();
		name2 = (*k)->shapeName();

		m_info1 = (*i)->objectInfo();
		m_info2 = (*k)->objectInfo();

		if (name1 == "Circle" && name2 == "Circle")
			isCollision = CC_collision(m_info1, m_info2, v_intersectionPoint); // boolean function
		else if (name1 == "Circle" && name2 == "Rectangle")
			isCollision = CR_collision(m_info1, m_info2, v_intersectionPoint);
		else if (name1 == "Rectangle" && name2 == "Circle")
			isCollision = CR_collision(m_info2, m_info1, v_intersectionPoint);
		else if (name1 == "Rectangle" && name2 == "Rectangle")
			isCollision = RR_collision(m_info1, m_info2, v_intersectionPoint);

		if (isCollision)
		{
			(*i)->onCollision(v_intersectionPoint);
			(*k)->onCollision(v_intersectionPoint);
		}
	}
}

bool Game::CC_collision(t_info pC1, t_info pC2, sf::Vector2f &v_interPoint)
{
	std::cout << "ERROR2\n";
	return false;
}

bool Game::CR_collision(t_info pC, t_info pR, sf::Vector2f &v_interPoint)
{
	float r_b, r_a, c_a, c_b; /// "r" is for rectangle, "c" is for circle, "a" and "b" are parameters of line function y = ax + b
	sf::Vector2f * v1;
	sf::Vector2f * v2;
	sf::Vector2f v_intersection;
	float radius = pC[1].x;
	bool isPointInCircle = false;
	bool isPointOnSegment = false;
	bool isRecVertexInCircle = false;

	/*for (it_info i = pR.begin() + 2; i != pR.end(); ++i)
	{
		//std::cout << "v num " << i - pR.begin() + 2 << ": " << (*i).x << ", " << (*i).y << "\n";
		Circle c((*i).x, (*i).y,10, "");
		draw(c);
	}*/

	int vertexCount = pR.size() - 2; /// From element third list of points begins

	for (int i = 0; i < vertexCount; ++i)
	{
		v1 = &pR[2 + i];
		if (i == vertexCount + 1)
			v2 = &pR[2];
		else
			v2 = &pR[2 + i + 1];
		
		r_a = angularCoefficient(v1, v2);
		/// Handle exceptions
		if (r_a == 0)
		{
			if (v1->x == v2->x)
			{
				v_intersection.x = v1 -> x;
				v_intersection.y = pC[0].y;
			}
			else if (v1->y == v2->y)
			{
				v_intersection.x =  pC[0].x;
				v_intersection.y = v1->y;
			}
		}
		else
		{
			float r_b = absoluteTerm(v1, v2);
			/// Obliczam parametry a i b prostej prostopadlej do |v1v2| przechodzacej przez srodek okregu
			float c_a = -r_a;
			float c_b = pC[0].y - pC[0].x*c_a;
			/// Obliczam punkt przeciecia sie obu prostych
			v_intersection.x = (c_b - r_b) / (2 * r_a);
			v_intersection.y = (c_b - r_b) / r_a + r_b;
		}
		/// Warunki kolizji
		/// if distance == radius, then there is no collision!
		isPointInCircle = distanceBetweenPoints(&pC[0], &v_intersection) < radius ? true : false; /// True if intersection is in the circle
		isPointOnSegment = isBetweenPoints(&v_intersection, v1, v2);
		if (!(isPointInCircle && isPointOnSegment))
			isRecVertexInCircle = distanceBetweenPoints(v1, &pC[0]) < radius || distanceBetweenPoints(v2, &pC[0]) < radius ? true : false;
		else
			isRecVertexInCircle = false;

		if (isRecVertexInCircle || (isPointInCircle && isPointOnSegment))
		{
			/*std::cout << "collision cords " << ": " << v_intersection.x << ", " << v_intersection.y << "\n";
			Circle c(v_intersection.x, v_intersection.y, 10, "");
			draw(c);*/
			if(!isRecVertexInCircle)
				v_interPoint = v_intersection;
			else
				v_interPoint = distanceBetweenPoints(v1, &pC[0]) < radius ? *v1 : *v2;
				
			return true;
		}
	}
	return false;
}

bool Game::RR_collision(t_info pR1, t_info pR2, sf::Vector2f &v_interPoint)
{
	std::cout << "ERROR\n";
	return false;
}