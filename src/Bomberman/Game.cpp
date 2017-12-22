#include "Game.h"
#include "Scene.h"
#include "Menu.h"
#include "Level.h"
#include "Ranking.h"



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

		if (oldState != currentSc->estado) {		//Control escenas

			switch (currentSc->estado)
			{
			case INMENU:

				std::cout << "MENU" << std::endl;

				break;

			case TOMENU:

				currentSc = new Menu();

				std::cout << "MENU" << std::endl;

				break;

			case RANKING:

				currentSc = new Ranking(oldState!=INMENU);
				std::cout << "RANKING" << std::endl;

				break;

			case PLAY1:

				currentSc = new Level(DEFAULT);

				std::cout << "PLAY1" << std::endl; //debug

				break;

			case PLAY2:

				currentSc = new Level(LEVEL2);
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

	IMG_Quit();			//termina bucle i es tanca SDL
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}