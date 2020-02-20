#include <SFML\Graphics.hpp>
#include "Game.h"
#include "TileMap.h"
int main()
{ 
	Game* game = new Game();
	game->Run();
	return 0;
}