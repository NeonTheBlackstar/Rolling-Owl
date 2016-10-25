#include "Header.h"

int main()
{
	Game gameInstance(500, 500, "The Game");
	gameInstance.setUpWorld(0.1, 200);

	gameInstance.loadEntityOnQueue(new Player(250, 250, 30, 0.5f, sf::Vector2f(0.02, 10), "happy.png"));
	gameInstance.loadEntityOnQueue(new Static(250, 100, sf::Vector2f(250, 50), "texture.png"));
	gameInstance.loadEntityOnQueue(new Static(125, 175, sf::Vector2f(100, 50), "texture.png"));
	gameInstance.loadEntityOnQueue(new Static(250, 425, sf::Vector2f(200, 50), "texture.png"));

	gameInstance.MainLoop();
	return 0;
}