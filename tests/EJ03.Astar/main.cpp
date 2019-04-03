#include <defines.h> 
#include <Node.h>
#include <sprite.h>
#include <vector>
#include <iostream>
#include <limits>
#include "texture.h"
#include <algorithm>
#include <Game.h>
#include <Read_Map.h>
#include <../include/SDL/SDL.h>
#include <window.h>
#include <ctime>

#define SDL_MAIN_HANDLED
int main(int argc, char* argv[]) {
	//Texture t = Texture();
	//t.loadFromFile(MAP);
	srand(time(NULL));

	Window::instance().init(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

	{
		Game game;

		game.init();
		game.start();
		game.shutdown();
	}

	Window::instance().shutdown();

	getchar();
	return 0;
}

