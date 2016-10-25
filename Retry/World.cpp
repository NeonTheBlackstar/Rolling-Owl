#include "Header.h"

void World::setUpWorld(float _grv, float _gmS)
{
	gravity = _grv;
	gameSpeed = _gmS;
}

void World::loadEntityOnQueue(Entity * pE)
{
	v_entities.push_back(pE);
}