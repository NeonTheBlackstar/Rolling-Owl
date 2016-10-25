#include "Header.h"

Entity::Entity(std::string textureName)
	: isStatic(false), enableCollisions(true)
{
	if (textureName != "" && !texture.loadFromFile(textureName))
		std::cout << "\nCannot load texture from path \"" << textureName << "\"!\n";
}

Entity::~Entity() {}

void Entity::update(Game * pGame) {}

void Entity::drawShape(Game * pGame) {}

std::string Entity::shapeName() { return ""; }

t_info Entity::objectInfo() { t_info empty; return empty; }

void Entity::onCollision(sf::Vector2f v_interPoint) { }