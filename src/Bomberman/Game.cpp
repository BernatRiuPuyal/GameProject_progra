#include "Game.h"
#include "Scene.h"
#include "Menu.h"
#include "Level.h"



Game::Game()
{
	currentSc = new Menu(); //Escena de inicio
}

Game::~Game()
{
}

void Game::loop()
{
	while (currentSc->estado != QUIT)
	{
		currentSc->inputHandler();
		currentSc->update();
		currentSc->draw();

		if (oldState != currentSc->estado) {

			switch (currentSc->estado)
			{
			case INMENU:

				std::cout << "MENU" << std::endl;

				break;

			case RANKING:

				std::cout << "RANKING" << std::endl;

				break;

			case PLAY1:

				std::cout << "PLAY1" << std::endl;
				currentSc = new Level();

				break;

			case PLAY2:

				std::cout << "PLAY2" << std::endl;

				break;

			case QUIT:

				std::cout << "QUIT" << std::endl;

				break;

			case TURNMUSIC:

				std::cout << "TURNMUSIC" << std::endl;

				break;
			}
		}

		oldState = currentSc->estado;
	}

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}