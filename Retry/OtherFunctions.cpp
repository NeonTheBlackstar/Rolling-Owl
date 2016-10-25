#include "Header.h"

float distanceBetweenPoints(sf::Vector2f * v1, sf::Vector2f * v2)
{
	return (v2->x - v1->x) != 0 || (v2->y - v1->y) != 0 ? sqrtf(pow(v2->x - v1->x, 2) + pow(v2->y - v1->y, 2)) : 0;
}

float angularCoefficient(sf::Vector2f * v1, sf::Vector2f * v2)
{
	return (v1->x - v2->x) != 0 ? (v1->y - v2->y) / (v1->x - v2->x) : 0;
}

float absoluteTerm(sf::Vector2f * v1, sf::Vector2f * v2)
{
	return (v1->x - v2->x) != 0 ? (v2->x*v1->y - v1->x*v2->y) / (v1->x - v2->x) : 0;
}

float absoluteTerm(float a, sf::Vector2f * v)
{
	return v->y - (a*v->x);
}

/// All points should lay on the same line
bool isBetweenPoints(sf::Vector2f * point, sf::Vector2f * v1, sf::Vector2f * v2)
{
	float v1_to_v2 = distanceBetweenPoints(v1, v2);
	float point_to_v1 = distanceBetweenPoints(point, v1);
	float point_to_v2 = distanceBetweenPoints(point, v2);
	return point_to_v1 <= v1_to_v2 && point_to_v2 <= v1_to_v2 ? true : false;
}