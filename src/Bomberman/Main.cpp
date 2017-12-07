#include <SDL.h>
#include <iostream>
#include "Menu.h"
#include "Game.h"
#include "Scene.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>


int main(int, char*[]) {

	Game _game;

	while (true) 
	{ 
		_game.loop();
	}



	return 0;
}